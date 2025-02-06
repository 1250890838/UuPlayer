qt_add_library(gui STATIC)

set(plain_qml_files
    qml/Main.qml
    qml/leftNavigationPanel/LeftNavigationPanel.qml
    qml/leftNavigationPanel/NavigationPanelItem.qml
    qml/stackPages/cloudMusicSelectedPage/CloudMusicSelectedPage.qml
    qml/stackPages/cloudMusicSelectedPage/NavigateLogic.js
    qml/stackPages/cloudMusicSelectedPage/PlaylistSquareSubpage.qml
    qml/stackPages/cloudMusicSelectedPage/RankingSubpage.qml
    qml/stackPages/cloudMusicSelectedPage/SelectiveSubpage.qml
    qml/stackPages/cloudMusicSelectedPage/SingerSubpage.qml
    qml/stackPages/cloudMusicSelectedPage/TabsBar.qml
    qml/stackPages/cloudMusicSelectedPage/CTab.qml
    qml/stackPages/cloudMusicSelectedPage/VipSubpage.qml
    qml/stackPages/CommunityPage.qml
    qml/stackPages/DownloadManagePage.qml
    qml/stackPages/FavorMusicPage.qml
    qml/stackPages/LocalMusicPage.qml
    qml/stackPages/PodcastPage.qml
    qml/stackPages/RecentPlayPage.qml
    qml/titleBar/TitleBar.qml
    qml/titleBar/LoginDialog.qml
)

set(singletons_qml_files
    qml/assets/Icons.qml
    qml/assets/Skins.qml
)

set(custom_shared_qml_files 
    qml/components/button/IconButton.qml
    qml/components/button/IconLabel.qml
    qml/components/button/TextIconButton.qml
    qml/components/other/PlaylistItem.qml
)

set(js_files
    qml/leftNavigationPanel/NavigateLogic.js
)
#[[ set_source_files_properties(${qml_singletons}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
]]

set(image_files 
    images/app_icon.png
    images/button_choice_music.svg
    images/button_choice_music_selected.svg
    images/button_download_manager.svg
    images/button_download_manager_selected.svg
    images/button_favor_music.svg
    images/button_favor_music_selected.svg
    images/button_local_music.svg
    images/button_local_music_selected.svg
    images/button_movement.svg
    images/button_movement_selected.svg
    images/button_podcast.svg
    images/button_podcast_selected.svg
    images/button_recent_play.svg
    images/button_recent_play_selected.svg
    images/button_minimize.svg
    images/button_maximize.svg
    images/button_close.svg
    images/default_user_profile.svg
    images/button_skin.svg
    images/qrcode_scan_sample.png
    )

set(cpp_files

)

target_include_directories(gui PRIVATE "./cpp")

qt_add_qml_module(gui
    URI "gui"
    VERSION 1.0
    QML_FILES
    ${plain_qml_files}
    ${singletons_qml_files}
    ${custom_shared_qml_files}
    ${js_files}
    SOURCES
    cpp/UuWindow.cc 
    cpp/UuWindow.h
    #   ${cpp_files}
    RESOURCE_PREFIX /
    RESOURCES
    ${image_files}
        qml/components/qmldir
    IMPORT_PATH
        qml/
        QML_FILES qml/stackPages/skinPage/SkinPage.qml
        QML_FILES qml/stackPages/skinPage/SkinItem.qml
        QML_FILES qml/components/other/CatlistItem.qml
        QML_FILES qml/stackPages/cloudMusicSelectedPage/CatlistDialog.qml
        QML_FILES qml/components/other/RoundedImage.qml
        QML_FILES qml/components/other/RoundedRectangle.qml
        QML_FILES qml/PlaylistDetailPage.qml
        QML_FILES qml/components/utils.js
)

target_link_libraries(gui PRIVATE Qt6::Quick)

