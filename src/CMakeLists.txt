cmake_minimum_required(VERSION 3.21)

project(uu VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Gui Multimedia Network Concurrent)
qt_standard_project_setup(REQUIRES 6.5)
find_package(QWindowKit COMPONENTS Core Widgets Quick REQUIRED)

set(qml_singletons
    ui/qml/assets/Icons.qml
    ui/qml/assets/Skins.qml
)
set_source_files_properties(${qml_singletons}
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

set(qml_files
    ui/qml/Main.qml
    ui/qml/leftNavigationPanel/LeftNavigationPanel.qml
    ui/qml/leftNavigationPanel/NavigateLogic.js
    ui/qml/leftNavigationPanel/NavigationPanelItem.qml
    ui/qml/lyricsView/DesktopLyricWindow.qml
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
    ui/qml/playlistDetail/SortHeaderItem.qml
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
    ui/qml/stackPages/cloudMusicSelectedPage/SingerSubpage.qml
    ui/qml/stackPages/cloudMusicSelectedPage/TabsBar.qml
    ui/qml/stackPages/cloudMusicSelectedPage/VipSubpage.qml
    ui/qml/stackPages/localMusicPage/LocalMusicPage.qml
    ui/qml/stackPages/localMusicPage/SearchBox.qml
    ui/qml/stackPages/localMusicPage/SelectLocalDirsDialog.qml
    ui/qml/stackPages/skinPage/SkinItem.qml
    ui/qml/stackPages/skinPage/SkinPage.qml
    ui/qml/titleBar/LoginDialog.qml
    ui/qml/titleBar/TitleBar.qml
)

set(ui_base_files
    ui_base/CScrollBar.qml
    ui_base/CTab.qml
    ui_base/CarouselView.qml
    ui_base/CatlistItem.qml
    ui_base/IconButton.qml
    ui_base/IconLabel.qml
    ui_base/PlaylistItem.qml
    ui_base/RoundedImage.qml
    ui_base/RoundedRectangle.qml
    ui_base/SearchBar.qml
    ui_base/TextIconButton.qml
    ui_base/Toast.qml
    ui_base/UScrollBar.qml
    ui_base/UTextEdit.qml
    ui_base/Utils.js
)

foreach(qml_file IN LISTS qml_files qml_singletons ui_base_files)
    get_filename_component(qml_abs "${qml_file}" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    if(qml_file MATCHES "^ui_base/")
        get_filename_component(qml_alias "${qml_abs}" NAME)
    else()
        file(RELATIVE_PATH qml_alias "${CMAKE_CURRENT_SOURCE_DIR}/ui/qml" "${qml_abs}")
    endif()
    set_source_files_properties(${qml_file} PROPERTIES QT_RESOURCE_ALIAS "${qml_alias}")
endforeach()

set(image_files
    ui/images/app_icon.png
    ui/images/audio_wave.gif
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
    ui/images/button_lyrics.svg
    ui/images/button_lyrics_hovered.svg
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
    ui/images/desktoplyric_close.svg
    ui/images/desktoplyric_locked.svg
    ui/images/desktoplyric_next.svg
    ui/images/desktoplyric_pause.svg
    ui/images/desktoplyric_play.svg
    ui/images/desktoplyric_previous.svg
    ui/images/desktoplyric_setting.svg
    ui/images/female.svg
    ui/images/male.svg
    ui/images/qrcode_scan_sample.png
    ui/images/search.svg
)

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
    core/entities/aristitem.h
    core/entities/useritem.h
    core/entities/mediaitem.h
    core/entities/playlistitem.h
    core/entities/commentitem.h
    core/entities/lyrictypes.h
    core/entities/homepageinfo.h
    core/repositories/authrepository.h
    core/repositories/authrepository.cc
    core/repositories/commentrepository.h
    core/repositories/commentrepository.cc
    core/repositories/homepagerepository.h
    core/repositories/homepagerepository.cc
    core/repositories/playlistrepository.h
    core/repositories/playlistrepository.cc
    core/repositories/songrepository.h
    core/repositories/songrepository.cc

    viewmodels/featuredplaylisthubcontroller.h
    viewmodels/featuredplaylisthubcontroller.cc
    viewmodels/homepagecontroller.h
    viewmodels/homepagecontroller.cc
    viewmodels/logincontroller.h
    viewmodels/logincontroller.cc
    viewmodels/lyricsviewcontroller.h
    viewmodels/lyricsviewcontroller.cc
    viewmodels/playcontroller.h
    viewmodels/playcontroller.cc
    viewmodels/playlistdetailscontroller.h
    viewmodels/playlistdetailscontroller.cc
    viewmodels/models/mediaitemfilterproxymodel.h
    viewmodels/models/mediaitemfilterproxymodel.cc
    viewmodels/models/mediaitemmodel.h
    viewmodels/models/mediaitemmodel.cc
    viewmodels/models/playlistitemmodel.h
    viewmodels/models/playlistitemmodel.cc

    ui/imageprovider.h
    ui/imageprovider.cc
    ui/imagestore.h
    ui/imagestore.cc
    ui/thememanager.h
    ui/thememanager.cc
    ui/windowhelper.h
    ui/windowhelper.cc
)

qt_add_qml_module(uu
    URI app
    VERSION 1.0
    QML_FILES
        ${qml_files}
        ${qml_singletons}
        ${ui_base_files}
    SOURCES
        viewmodels/featuredplaylisthubcontroller.h
        viewmodels/featuredplaylisthubcontroller.cc
        viewmodels/homepagecontroller.h
        viewmodels/homepagecontroller.cc
        viewmodels/playlistdetailscontroller.h
        viewmodels/playlistdetailscontroller.cc
        ui/windowhelper.h
        ui/windowhelper.cc
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
    Qt6::Concurrent
    QWindowKit::Quick
)
