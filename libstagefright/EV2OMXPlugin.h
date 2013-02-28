/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef EV2_OMX_PLUGIN_H_

#define EV2_OMX_PLUGIN_H_

#include <OMXPluginBase.h>

namespace android {

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

struct OmxPlugin
{
    void *dl_handle;
    SymbolTable sym_table;
};

struct OMFPlugin : public OMXPluginBase {
    OMFPlugin();
    virtual ~OMFPlugin();

    virtual OMX_ERRORTYPE makeComponentInstance(
            const char *name,
            const OMX_CALLBACKTYPE *callbacks,
            OMX_PTR appData,
            OMX_COMPONENTTYPE **component);

    virtual OMX_ERRORTYPE destroyComponentInstance(
            OMX_COMPONENTTYPE *component);

    virtual OMX_ERRORTYPE enumerateComponents(
            OMX_STRING name,
            size_t size,
            OMX_U32 index);

    virtual OMX_ERRORTYPE getRolesOfComponent(
            const char *name,
            Vector<String8> *roles);

private:
    OMFPlugin(const OMFPlugin &);
    OMFPlugin &operator=(const OMFPlugin &);
    OmxPlugin omx_plugin;
};

}  // namespace android


#endif  // EV2_OMX_PLUGIN_H_
