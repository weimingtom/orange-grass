ENGINEPATH := sources/engine/src

LOCAL_C_INCLUDES += sources/engine/include
LOCAL_SRC_FILES +=  $(ENGINEPATH)/ogcamera.cpp \
                    $(ENGINEPATH)/ogcoloreffectshader.cpp \
                    $(ENGINEPATH)/ogeffect.cpp \
                    $(ENGINEPATH)/ogmodelskeleton.cpp \
                    $(ENGINEPATH)/ogeffectsmanager.cpp \
                    $(ENGINEPATH)/ogemitter.cpp \
                    $(ENGINEPATH)/ogemitteranimatedbb.cpp \
                    $(ENGINEPATH)/ogemitterglow.cpp \
                    $(ENGINEPATH)/ogemitterlightflash.cpp \
                    $(ENGINEPATH)/ogemitterparticlechain.cpp \
                    $(ENGINEPATH)/ogemitterpulseglow.cpp \
                    $(ENGINEPATH)/ogemitterringwave.cpp \
                    $(ENGINEPATH)/ogemitterrotatingsparks.cpp \
                    $(ENGINEPATH)/ogemitterscrollingray.cpp \
                    $(ENGINEPATH)/ogemittertrail.cpp \
                    $(ENGINEPATH)/ogfog.cpp \
                    $(ENGINEPATH)/ogfpscounter.cpp \
                    $(ENGINEPATH)/ogglobalvarstable.cpp \
                    $(ENGINEPATH)/oginputdispatcher.cpp \
                    $(ENGINEPATH)/oglight.cpp \
                    $(ENGINEPATH)/ogmaterial.cpp \
                    $(ENGINEPATH)/ogmatrix.cpp \
                    $(ENGINEPATH)/ogmesh.cpp \
                    $(ENGINEPATH)/ogmodel.cpp \
                    $(ENGINEPATH)/ogmodelshader.cpp \
                    $(ENGINEPATH)/ogmodelconfig.cpp \
                    $(ENGINEPATH)/ogquaternion.cpp \
                    $(ENGINEPATH)/ogrenderer.cpp \
                    $(ENGINEPATH)/ogrendertarget.cpp \
                    $(ENGINEPATH)/ogresource.cpp \
                    $(ENGINEPATH)/ogresourcefile.cpp \
                    $(ENGINEPATH)/ogresourcemgr.cpp \
                    $(ENGINEPATH)/ogsettingsreader.cpp \
                    $(ENGINEPATH)/ogshader.cpp \
                    $(ENGINEPATH)/ogshadowedsceneshader.cpp \
                    $(ENGINEPATH)/ogshadowedtranspsceneshader.cpp \
                    $(ENGINEPATH)/ogshadowmodelshader.cpp \
                    $(ENGINEPATH)/ogshadowtranspmodelshader.cpp \
                    $(ENGINEPATH)/ogtransparentmodelshader.cpp \
                    $(ENGINEPATH)/ogshadermanager.cpp \
                    $(ENGINEPATH)/ogsprite.cpp \
                    $(ENGINEPATH)/ogspriteshader.cpp \
                    $(ENGINEPATH)/ogstatistics.cpp \
                    $(ENGINEPATH)/ogtextrenderer.cpp \
                    $(ENGINEPATH)/ogtextshader.cpp \
                    $(ENGINEPATH)/ogtexture.cpp \
                    $(ENGINEPATH)/ogvector.cpp \
                    $(ENGINEPATH)/ogvertexbuffers.cpp \
                    $(ENGINEPATH)/ogdynvertexbuffers.cpp \
                    $(ENGINEPATH)/OrangeGrass.cpp
