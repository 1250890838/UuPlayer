cmake_minimum_required(VERSION 3.21)

project(uu VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Gui Multimedia Network)
qt_standard_project_setup(REQUIRES 6.5)
find_package(QWindowKit COMPONENTS Core Widgets Quick REQUIRED)

set(qml_singletons
    ui/qml/assets/Icons.qml
    ui/qml/assets/Skins.qml
    ui/qml/components/Utils.qml
)
set_source_files_properties(${qml_singletons}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)


set(qml_files
    ui/qml/Main.qml
    ui/qml/components/button/IconButton.qml
    ui/qml/components/button/IconLabel.qml
    ui/qml/components/button/TextIconButton.qml
    ui/qml/components/edit/UTextEdit.qml
    ui/qml/components/other/CScrollBar.qml
    ui/qml/components/other/CTab.qml
    ui/qml/components/other/CatlistItem.qml
    ui/qml/components/other/PlaylistItem.qml
    ui/qml/components/other/RoundedImage.qml
    ui/qml/components/other/RoundedRectangle.qml
    ui/qml/components/other/UScrollBar.qml
    ui/qml/leftNavigationPanel/LeftNavigationPanel.qml
    ui/qml/leftNavigationPanel/NavigateLogic.js
    ui/qml/leftNavigationPanel/NavigationPanelItem.qml
    ui/qml/lyricsView/LyricItem.qml
    ui/qml/lyricsView/LyricsViewPage.qml
    ui/qml/lyricsView/RecordPlayer.qml
    ui/qml/playbackBar/AlbumDisplay.qml
    ui/qml/playbackBar/PlaybackBar.qml
    ui/qml/playbackBar/UuSlider.qml
    ui/qml/playbackBar/VolumeControlButton.qml
    ui/qml/playbacklist/PlaybacklistItem.qml
    ui/qml/playbacklist/PlaybacklistPage.qml
    ui/qml/playlistDetail/CommentItem.qml
    ui/qml/playlistDetail/MediaItem.qml
    ui/qml/playlistDetail/PlaylistDetailPage.qml
    ui/qml/playlistDetail/SubscriberItem.qml
    ui/qml/stackPages/CommunityPage.qml
    ui/qml/stackPages/DownloadManagePage.qml
    ui/qml/stackPages/FavorMusicPage.qml
    ui/qml/stackPages/PodcastPage.qml
    ui/qml/stackPages/RecentPlayPage.qml
    ui/qml/stackPages/cloudMusicSelectedPage/CatlistDialog.qml
    ui/qml/stackPages/cloudMusicSelectedPage/CloudMusicSelectedPage.qml
    ui/qml/stackPages/cloudMusicSelectedPage/NavigateLogic.js
    ui/qml/stackPages/cloudMusicSelectedPage/PlaylistSquareSubpage.qml
    ui/qml/stackPages/cloudMusicSelectedPage/RankingSubpage.qml
    ui/qml/stackPages/cloudMusicSelectedPage/SelectiveSubpage.qml
    ui/qml/stackPages/cloudMusicSelectedPage/SingerSubPage.qml
    ui/qml/stackPages/cloudMusicSelectedPage/TabsBar.qml
    ui/qml/stackPages/cloudMusicSelectedPage/VipSubpage.qml
    ui/qml/stackPages/localMusicPage/LocalMusicPage.qml
    ui/qml/stackPages/localMusicPage/SearchBox.qml
    ui/qml/stackPages/localMusicPage/SelectLocalDirsDialog.qml
    ui/qml/stackPages/localMusicPage/SortHeaderItem.qml
    ui/qml/stackPages/skinPage/SkinItem.qml
    ui/qml/stackPages/skinPage/SkinPage.qml
    ui/qml/titleBar/LoginDialog.qml
    ui/qml/titleBar/TitleBar.qml
)

set(image_files
    ui/images/app_icon.png
    ui/images/button_choice_music.svg
    ui/images/button_choice_music_selected.svg
    ui/images/button_close.svg
    ui/images/button_comment_item_comment.svg
    ui/images/button_comment_item_like.svg
    ui/images/button_comment_item_share.svg
    ui/images/button_down.svg
    ui/images/button_download_manager.svg
    ui/images/button_download_manager_selected.svg
    ui/images/button_favor_music.svg
    ui/images/button_favor_music_selected.svg
    ui/images/button_fullscreen.svg
    ui/images/button_local_music.svg
    ui/images/button_local_music_selected.svg
    ui/images/button_maximize.svg
    ui/images/button_minimize.svg
    ui/images/button_more.svg
    ui/images/button_movement.svg
    ui/images/button_movement_selected.svg
    ui/images/button_normalize.svg
    ui/images/button_pause.svg
    ui/images/button_pause_gray.svg
    ui/images/button_play.svg
    ui/images/button_play_gray.svg
    ui/images/button_playbackbar_next.svg
    ui/images/button_playbackbar_pause.svg
    ui/images/button_playbackbar_play.svg
    ui/images/button_playbackbar_playlist.svg
    ui/images/button_playbackbar_previous.svg
    ui/images/button_playbackbar_volumn_close.svg
    ui/images/button_playbackbar_volumn_open.svg
    ui/images/button_playbackmode_listloop.svg
    ui/images/button_playbackmode_sequential.svg
    ui/images/button_playbackmode_shuffle.svg
    ui/images/button_playbackmode_singleloop.svg
    ui/images/button_podcast.svg
    ui/images/button_podcast_selected.svg
    ui/images/button_recent_play.svg
    ui/images/button_recent_play_selected.svg
    ui/images/button_refresh.svg
    ui/images/button_skin.svg
    ui/images/button_subscribed.svg
    ui/images/default_user_profile.svg
    ui/images/qrcode_scan_sample.png
    ui/images/search.svg
)

foreach(qml_file IN LISTS qml_files qml_singletons)
    get_filename_component(qml_abs "${qml_file}" ABSOLUTE
        BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    file(RELATIVE_PATH qml_alias "${CMAKE_CURRENT_SOURCE_DIR}/ui/qml" "${qml_abs}")
    set_source_files_properties(${qml_file} PROPERTIES QT_RESOURCE_ALIAS "${qml_alias}")
endforeach()

foreach(image_file IN LISTS image_files)
    get_filename_component(image_name "${image_file}" NAME)
    set_source_files_properties(${image_file} PROPERTIES QT_RESOURCE_ALIAS "images/${image_name}")
endforeach()

qt_add_executable(uu
    main.cc

    app/appcontext.h
    app/appcontext.cc

    core/apiclient.h
    core/apiclient.cc
    core/apiendpoints.h
    core/mappers.h
    core/mappers.cc
    core/audioplayer.h
    core/audioplayer.cc

    core/entities/types.h
    core/entities/albumitem.h
    core/entities/artistitem.h
    core/entities/useritem.h
    core/entities/mediaitem.h
    core/entities/playlistitem.h
    core/entities/commentitem.h

    core/repositories/authrepository.h
    core/repositories/authrepository.cc
    core/repositories/commentrepository.h
    core/repositories/commentrepository.cc
    core/repositories/playlistrepository.h
    core/repositories/playlistrepository.cc
    core/repositories/songrepository.h
    core/repositories/songrepository.cc

    viewmodels/logincontroller.h
    viewmodels/logincontroller.cc
    viewmodels/playcontroller.h
    viewmodels/playcontroller.cc
    viewmodels/playlistdetailcontroller.h
    viewmodels/playlistdetailcontroller.cc
    viewmodels/playlisthubcontroller.h
    viewmodels/playlisthubcontroller.cc
    viewmodels/models/mediaitemmodel.h
    viewmodels/models/mediaitemmodel.cc
    viewmodels/models/playlistitemmodel.h
    viewmodels/models/playlistitemmodel.cc

    ui/imageprovider.h
    ui/imageprovider.cc
)

qt_add_qml_module(uu
    URI app
    VERSION 1.0
    QML_FILES
        ${qml_files}
        ${qml_singletons}
    SOURCES
        core/entities/albumitem.h
        core/entities/artistitem.h
        core/entities/useritem.h
        core/entities/mediaitem.h
        core/entities/playlistitem.h
        core/entities/commentitem.h
        viewmodels/models/mediaitemmodel.h
        viewmodels/models/playlistitemmodel.h
        viewmodels/playlisthubcontroller.h
        viewmodels/playlisthubcontroller.cc
        viewmodels/playlistdetailcontroller.h
        viewmodels/playlistdetailcontroller.cc
    RESOURCES
        ${image_files}
)

target_compile_features(uu PRIVATE cxx_std_20)
target_include_directories(uu PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/core/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/viewmodels
    ${CMAKE_CURRENT_SOURCE_DIR}/viewmodels/models
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_link_libraries(uu PRIVATE
    Qt6::Quick
    Qt6::Gui
    Qt6::Multimedia
    Qt6::Network
    QWindowKit::Quick
)
