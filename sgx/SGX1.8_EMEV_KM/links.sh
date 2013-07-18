source source.sh

export TARGET_PRODUCT=emev
export WORKDIR=$PWD
export SGX_DIR=$WORKDIR
export SGX_KM_DIR=$SGX_DIR/eurasia_km

cd $SGX_KM_DIR/eurasiacon/binary2_emev_android_release/target/kbuild/services4

rm ./3rdparty/dc_emxxfb_linux/emxxlfb_displayclass.c ; ln -s $SGX_KM_DIR/services4/3rdparty/dc_emxxfb_linux/emxxlfb_displayclass.c ./3rdparty/dc_emxxfb_linux/emxxlfb_displayclass.c
rm ./3rdparty/dc_emxxfb_linux/emxxlfb_linux.c        ; ln -s $SGX_KM_DIR/services4/3rdparty/dc_emxxfb_linux/emxxlfb_linux.c        ./3rdparty/dc_emxxfb_linux/emxxlfb_linux.c       
rm ./srvkm/bridged/bridged_pvr_bridge.c              ; ln -s $SGX_KM_DIR/services4/srvkm/bridged/bridged_pvr_bridge.c              ./srvkm/bridged/bridged_pvr_bridge.c             
rm ./srvkm/bridged/bridged_support.c                 ; ln -s $SGX_KM_DIR/services4/srvkm/bridged/bridged_support.c                 ./srvkm/bridged/bridged_support.c                
rm ./srvkm/bridged/sgx/bridged_sgx_bridge.c          ; ln -s $SGX_KM_DIR/services4/srvkm/bridged/sgx/bridged_sgx_bridge.c          ./srvkm/bridged/sgx/bridged_sgx_bridge.c         
rm ./srvkm/common/buffer_manager.c                   ; ln -s $SGX_KM_DIR/services4/srvkm/common/buffer_manager.c                   ./srvkm/common/buffer_manager.c                  
rm ./srvkm/common/deviceclass.c                      ; ln -s $SGX_KM_DIR/services4/srvkm/common/deviceclass.c                      ./srvkm/common/deviceclass.c                     
rm ./srvkm/common/devicemem.c                        ; ln -s $SGX_KM_DIR/services4/srvkm/common/devicemem.c                        ./srvkm/common/devicemem.c                       
rm ./srvkm/common/handle.c                           ; ln -s $SGX_KM_DIR/services4/srvkm/common/handle.c                           ./srvkm/common/handle.c                          
rm ./srvkm/common/hash.c                             ; ln -s $SGX_KM_DIR/services4/srvkm/common/hash.c                             ./srvkm/common/hash.c                            
rm ./srvkm/common/lists.c                            ; ln -s $SGX_KM_DIR/services4/srvkm/common/lists.c                            ./srvkm/common/lists.c                           
rm ./srvkm/common/mem.c                              ; ln -s $SGX_KM_DIR/services4/srvkm/common/mem.c                              ./srvkm/common/mem.c                             
rm ./srvkm/common/mem_debug.c                        ; ln -s $SGX_KM_DIR/services4/srvkm/common/mem_debug.c                        ./srvkm/common/mem_debug.c                       
rm ./srvkm/common/metrics.c                          ; ln -s $SGX_KM_DIR/services4/srvkm/common/metrics.c                          ./srvkm/common/metrics.c                         
rm ./srvkm/common/osfunc_common.c                    ; ln -s $SGX_KM_DIR/services4/srvkm/common/osfunc_common.c                    ./srvkm/common/osfunc_common.c                   
rm ./srvkm/common/pdump_common.c                     ; ln -s $SGX_KM_DIR/services4/srvkm/common/pdump_common.c                     ./srvkm/common/pdump_common.c                    
rm ./srvkm/common/perproc.c                          ; ln -s $SGX_KM_DIR/services4/srvkm/common/perproc.c                          ./srvkm/common/perproc.c                         
rm ./srvkm/common/power.c                            ; ln -s $SGX_KM_DIR/services4/srvkm/common/power.c                            ./srvkm/common/power.c                           
rm ./srvkm/common/pvrsrv.c                           ; ln -s $SGX_KM_DIR/services4/srvkm/common/pvrsrv.c                           ./srvkm/common/pvrsrv.c                          
rm ./srvkm/common/queue.c                            ; ln -s $SGX_KM_DIR/services4/srvkm/common/queue.c                            ./srvkm/common/queue.c                           
rm ./srvkm/common/ra.c                               ; ln -s $SGX_KM_DIR/services4/srvkm/common/ra.c                               ./srvkm/common/ra.c                              
rm ./srvkm/common/refcount.c                         ; ln -s $SGX_KM_DIR/services4/srvkm/common/refcount.c                         ./srvkm/common/refcount.c                        
rm ./srvkm/common/resman.c                           ; ln -s $SGX_KM_DIR/services4/srvkm/common/resman.c                           ./srvkm/common/resman.c                          
rm ./srvkm/devices/sgx/mmu.c                         ; ln -s $SGX_KM_DIR/services4/srvkm/devices/sgx/mmu.c                         ./srvkm/devices/sgx/mmu.c                        
rm ./srvkm/devices/sgx/pb.c                          ; ln -s $SGX_KM_DIR/services4/srvkm/devices/sgx/pb.c                          ./srvkm/devices/sgx/pb.c                         
rm ./srvkm/devices/sgx/sgxinit.c                     ; ln -s $SGX_KM_DIR/services4/srvkm/devices/sgx/sgxinit.c                     ./srvkm/devices/sgx/sgxinit.c                    
rm ./srvkm/devices/sgx/sgxkick.c                     ; ln -s $SGX_KM_DIR/services4/srvkm/devices/sgx/sgxkick.c                     ./srvkm/devices/sgx/sgxkick.c                    
rm ./srvkm/devices/sgx/sgxpower.c                    ; ln -s $SGX_KM_DIR/services4/srvkm/devices/sgx/sgxpower.c                    ./srvkm/devices/sgx/sgxpower.c                   
rm ./srvkm/devices/sgx/sgxreset.c                    ; ln -s $SGX_KM_DIR/services4/srvkm/devices/sgx/sgxreset.c                    ./srvkm/devices/sgx/sgxreset.c                   
rm ./srvkm/devices/sgx/sgxtransfer.c                 ; ln -s $SGX_KM_DIR/services4/srvkm/devices/sgx/sgxtransfer.c                 ./srvkm/devices/sgx/sgxtransfer.c                
rm ./srvkm/devices/sgx/sgxutils.c                    ; ln -s $SGX_KM_DIR/services4/srvkm/devices/sgx/sgxutils.c                    ./srvkm/devices/sgx/sgxutils.c                   
rm ./srvkm/env/linux/event.c                         ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/event.c                         ./srvkm/env/linux/event.c                        
rm ./srvkm/env/linux/mmap.c                          ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/mmap.c                          ./srvkm/env/linux/mmap.c                         
rm ./srvkm/env/linux/mm.c                            ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/mm.c                            ./srvkm/env/linux/mm.c                           
rm ./srvkm/env/linux/module.c                        ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/module.c                        ./srvkm/env/linux/module.c                       
rm ./srvkm/env/linux/mutex.c                         ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/mutex.c                         ./srvkm/env/linux/mutex.c                        
rm ./srvkm/env/linux/mutils.c                        ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/mutils.c                        ./srvkm/env/linux/mutils.c                       
rm ./srvkm/env/linux/osfunc.c                        ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/osfunc.c                        ./srvkm/env/linux/osfunc.c                       
rm ./srvkm/env/linux/osperproc.c                     ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/osperproc.c                     ./srvkm/env/linux/osperproc.c                    
rm ./srvkm/env/linux/pdump.c                         ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/pdump.c                         ./srvkm/env/linux/pdump.c                        
rm ./srvkm/env/linux/proc.c                          ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/proc.c                          ./srvkm/env/linux/proc.c                         
rm ./srvkm/env/linux/pvr_bridge_k.c                  ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/pvr_bridge_k.c                  ./srvkm/env/linux/pvr_bridge_k.c                 
rm ./srvkm/env/linux/pvr_debug.c                     ; ln -s $SGX_KM_DIR/services4/srvkm/env/linux/pvr_debug.c                     ./srvkm/env/linux/pvr_debug.c                    
rm ./system/emev/sysconfig.c                         ; ln -s $SGX_KM_DIR/services4/system/emev/sysconfig.c                         ./system/emev/sysconfig.c                        
rm ./system/emev/sysutils.c                          ; ln -s $SGX_KM_DIR/services4/system/emev/sysutils.c                          ./system/emev/sysutils.c       
