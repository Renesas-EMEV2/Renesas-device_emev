/*
 *  Testing OMX EV plugin
 */

#define LOG_NDEBUG 0
#define LOG_TAG "EV2OMXPlugin_Test"
#include <utils/Log.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <OMXPluginBase.h>
#include <binder/ProcessState.h>

struct SymbolTable
{
    OMX_ERRORTYPE (*init) (void);
    OMX_ERRORTYPE (*deinit) (void);
    OMX_ERRORTYPE (*get_handle) (OMX_HANDLETYPE *handle,
                                 OMX_STRING name,
                                 OMX_PTR data,
                                 OMX_CALLBACKTYPE *callbacks);
    OMX_ERRORTYPE (*free_handle) (OMX_HANDLETYPE handle);
    
    OMX_ERRORTYPE (*component_name_enum) (OMX_STRING cComponentName,
                                          OMX_U32 nNameLength,
                                          OMX_U32 nIndex);
    OMX_ERRORTYPE (*get_roles_of_component) (OMX_STRING compName, 
                                             OMX_U32 *pNumRoles,
                                             OMX_U8 **roles);
    OMX_ERRORTYPE (*set_log_mode) (OMX_U32 u32LogMode);
};

static int test(void) {

    void *dl_handle;
    SymbolTable sym_table;

    dl_handle = dlopen ("libomf_manager.so", RTLD_LAZY);
    if (!dl_handle)
    {
	ALOGE("libomf_manager.so dl open error");
        return 0;
    }
    ALOGI("libomf_manager.so dl open success (0x%08x)", (unsigned int)dl_handle);

    sym_table.init = *(OMX_ERRORTYPE (*)())dlsym (dl_handle, "OMX_Init");
    sym_table.deinit = *(OMX_ERRORTYPE (*)())dlsym (dl_handle, "OMX_Deinit");
    sym_table.get_handle = *(OMX_ERRORTYPE (*)(OMX_HANDLETYPE *handle,
                                 OMX_STRING name,
                                 OMX_PTR data,
                                 OMX_CALLBACKTYPE *callbacks))dlsym (dl_handle, "OMX_GetHandle");
    sym_table.free_handle = *(OMX_ERRORTYPE (*)(OMX_HANDLETYPE handle))dlsym (dl_handle, "OMX_FreeHandle");
    sym_table.component_name_enum = *(OMX_ERRORTYPE (*)(OMX_STRING cComponentName,
                                          OMX_U32 nNameLength,
                                          OMX_U32 nIndex))dlsym (dl_handle, "OMX_ComponentNameEnum");
    sym_table.get_roles_of_component = *(OMX_ERRORTYPE (*)(OMX_STRING compName, 
                                             OMX_U32 *pNumRoles,
                                             OMX_U8 **roles))dlsym (dl_handle, "OMX_GetRolesOfComponent");
    
    int fd = open("/dev/InterDSP/datamgr", O_RDWR);
    ALOGI("open /dev/InterDSP/datamgr -> ret: 0x%08x", fd);
    OMX_ERRORTYPE ret = sym_table.init();
    ALOGI("Plugin OMX_Init -> ret: 0x%08x", ret);

    return 0;

}

static void usage(const char *me) {
    fprintf(stderr, "usage: %s\n"
                    "  -h(elp)  Show this information\n"
                    "Use this to test EV2 OMX Plugin", me);

    exit(0);
}

int main(int argc, char **argv) {

    const char *me = argv[0];
    int res;

    while ((res = getopt(argc, argv, "hs:")) >= 0) {
        switch (res) {

            case '?':
                fprintf(stderr, "\n");
                // fall through

            case 'h':
            default:
            {
                usage(me);
                exit(1);
                break;
            }
        }
    }

    argc -= optind;
    argv += optind;

    if (argc == 0) {
        return test();
    }

    return 0;
}
