GAMEPATH := sources/skycrasher/game/src

LOCAL_C_INCLUDES += sources/skycrasher/game/include \
                    sources/engine/include

LOCAL_SRC_FILES +=  $(GAMEPATH)/Game.cpp \
                    $(GAMEPATH)/GameScreenController.cpp \
                    $(GAMEPATH)/GameSystem.cpp \
                    $(GAMEPATH)/LoadScreenController.cpp \
                    $(GAMEPATH)/ogactor.cpp \
                    $(GAMEPATH)/ogactorairbot.cpp \
                    $(GAMEPATH)/ogactorbonus.cpp \
                    $(GAMEPATH)/ogactorbot.cpp \
                    $(GAMEPATH)/ogactorbullet.cpp \
                    $(GAMEPATH)/ogactorgaussray.cpp \
                    $(GAMEPATH)/ogactorlandbot.cpp \
                    $(GAMEPATH)/ogactormanager.cpp \
                    $(GAMEPATH)/ogactormissile.cpp \
                    $(GAMEPATH)/ogactorparamsmgr.cpp \
                    $(GAMEPATH)/ogactorplasmamissile.cpp \
                    $(GAMEPATH)/ogactorplayer.cpp \
                    $(GAMEPATH)/ogactorstatic.cpp \
                    $(GAMEPATH)/ogairphysicalobject.cpp \
                    $(GAMEPATH)/oganimationcontroller.cpp \
                    $(GAMEPATH)/ogappsettings.cpp \
                    $(GAMEPATH)/ogbonusphysicalobject.cpp \
                    $(GAMEPATH)/ogbotfallingworker.cpp \
                    $(GAMEPATH)/ogbotflightworker.cpp \
                    $(GAMEPATH)/ogfinishlevelworker.cpp \
                    $(GAMEPATH)/oggamesequence.cpp \
                    $(GAMEPATH)/ogguibonusbar.cpp \
                    $(GAMEPATH)/ogguibutton.cpp \
                    $(GAMEPATH)/ogguilifebar.cpp \
                    $(GAMEPATH)/ogguiweaponpanel.cpp \
                    $(GAMEPATH)/oglandphysicalobject.cpp \
                    $(GAMEPATH)/oglevel.cpp \
                    $(GAMEPATH)/oglevelmanager.cpp \
                    $(GAMEPATH)/ogmissileflightworker.cpp \
                    $(GAMEPATH)/ogmissilephysicalobject.cpp \
                    $(GAMEPATH)/ogorientworker.cpp \
                    $(GAMEPATH)/ogphysicalobject.cpp \
                    $(GAMEPATH)/ogphysics.cpp \
                    $(GAMEPATH)/ogplayerphysicalobject.cpp \
                    $(GAMEPATH)/ogscenegraph.cpp \
                    $(GAMEPATH)/ogsgeffectnode.cpp \
                    $(GAMEPATH)/ogsglandscapenode.cpp \
                    $(GAMEPATH)/ogsgnode.cpp \
                    $(GAMEPATH)/ogspritepool.cpp \
                    $(GAMEPATH)/ogstabilizeworker.cpp \
                    $(GAMEPATH)/ogstaticphysicalobject.cpp \
                    $(GAMEPATH)/ogweapon.cpp \
                    $(GAMEPATH)/ogworker.cpp \
                    $(GAMEPATH)/StartMenuScreenController.cpp
