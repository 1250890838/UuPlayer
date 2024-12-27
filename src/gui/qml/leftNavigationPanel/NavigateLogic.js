function switchPage(item, page, record = true) {

    console.log(page instanceof LocalMusicPage);
    if (item === navigationPanel.currentItem) {
        console.log("same page!");
        return;
    }
    navigationPanel.currentItem = item;
    stackView.replace(page);
    if (record == true) {
        window.commands.push(function () {
            switchPage(item, page,false);
        });
    }
}