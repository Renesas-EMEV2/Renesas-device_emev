#define LOG_NDEBUG 0
#define LOG_TAG "EV2OMXPlugin"
#include "EV2OMXPlugin.h"
#include <utils/Log.h>

#include <dlfcn.h>

#include <HardwareAPI.h>
#include <ADebug.h>
 
namespace android {

extern "C" OMXPluginBase *createOMXPlugin() {
    return new OMFPlugin;
}

extern "C" void destroyOMXPlugin(OMXPluginBase *plugin) {
    delete plugin;
}

OMFPlugin::OMFPlugin() {

    omx_plugin.dl_handle = dlopen ("libomf_manager.so", RTLD_LAZY);
    if (!omx_plugin.dl_handle)
    {
		ALOGE("***OMFPlugin() dl open error!!");
        return;
    }
    ALOGI("***OMFPlugin() dl open success !!!!!!!!");

    omx_plugin.sym_table.init = *(OMX_ERRORTYPE (*)())dlsym (omx_plugin.dl_handle, "OMX_Init");
    omx_plugin.sym_table.deinit = *(OMX_ERRORTYPE (*)())dlsym (omx_plugin.dl_handle, "OMX_Deinit");
    omx_plugin.sym_table.get_handle = *(OMX_ERRORTYPE (*)(OMX_HANDLETYPE *handle,
                                 OMX_STRING name,
                                 OMX_PTR data,
                                 OMX_CALLBACKTYPE *callbacks))dlsym (omx_plugin.dl_handle, "OMX_GetHandle");
    omx_plugin.sym_table.free_handle = *(OMX_ERRORTYPE (*)(OMX_HANDLETYPE handle))dlsym (omx_plugin.dl_handle, "OMX_FreeHandle");
    omx_plugin.sym_table.component_name_enum = *(OMX_ERRORTYPE (*)(OMX_STRING cComponentName,
                                          OMX_U32 nNameLength,
                                          OMX_U32 nIndex))dlsym (omx_plugin.dl_handle, "OMX_ComponentNameEnum");
    omx_plugin.sym_table.get_roles_of_component = *(OMX_ERRORTYPE (*)(OMX_STRING compName, 
                                             OMX_U32 *pNumRoles,
                                             OMX_U8 **roles))dlsym (omx_plugin.dl_handle, "OMX_GetRolesOfComponent");
    
    omx_plugin.sym_table.init();
}

OMFPlugin::~OMFPlugin() {
    omx_plugin.sym_table.deinit();
    dlclose (omx_plugin.dl_handle);
}

OMX_ERRORTYPE OMFPlugin::makeComponentInstance(
        const char *name,
        const OMX_CALLBACKTYPE *callbacks,
        OMX_PTR appData,
        OMX_COMPONENTTYPE **component) {
	ALOGI("***run OMFPlugin ------- makeComponentInstance !!!!!!!!");
    return omx_plugin.sym_table.get_handle(
            reinterpret_cast<OMX_HANDLETYPE *>(component),
            const_cast<char *>(name),
            appData,
            const_cast<OMX_CALLBACKTYPE *>(callbacks));
}

OMX_ERRORTYPE OMFPlugin::destroyComponentInstance(
        OMX_COMPONENTTYPE *component) {
    ALOGI("***run OMFPlugin ------- destroyComponentInstance !!!!!!!!");
    return omx_plugin.sym_table.free_handle(component);
}

OMX_ERRORTYPE OMFPlugin::enumerateComponents(
        OMX_STRING name,
        size_t size,
        OMX_U32 index) {
    ALOGI("***run OMFPlugin ------- enumerateComponents !!!!!!!!");
    return omx_plugin.sym_table.component_name_enum (name, size, index);
}

OMX_ERRORTYPE OMFPlugin::getRolesOfComponent(
        const char *name,
        Vector<String8> *roles) {
    roles->clear();

    OMX_U32 numRoles;

    OMX_ERRORTYPE err =
        omx_plugin.sym_table.get_roles_of_component(
                const_cast<char *>(name),
                &numRoles,
                NULL);

    if (err != OMX_ErrorNone) {
        return err;
    }

    if (numRoles > 0) {
        OMX_U8 **array = new OMX_U8 *[numRoles];
        for (OMX_U32 i = 0; i < numRoles; ++i) {
            array[i] = new OMX_U8[OMX_MAX_STRINGNAME_SIZE];
        }

        OMX_U32 numRoles2;
		ALOGI("***run OMFPlugin ------- get_roles_of_component !!!!!!!!");
        err = omx_plugin.sym_table.get_roles_of_component(
                const_cast<char *>(name), &numRoles2, array);

        CHECK_EQ(err, OMX_ErrorNone);
        CHECK_EQ(numRoles, numRoles2);

        for (OMX_U32 i = 0; i < numRoles; ++i) {
            String8 s((const char *)array[i]);
            roles->push(s);

            delete[] array[i];
            array[i] = NULL;
        }

        delete[] array;
        array = NULL;
    }

    return OMX_ErrorNone;
}

}  // namespace android
