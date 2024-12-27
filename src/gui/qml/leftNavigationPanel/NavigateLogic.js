function switchPage(item, page) {
    if (item === navigationPanel.currentItem) {
        console.log("same page!");
        return;
    }
    navigationPanel.currentItem = item;
    stackView.replace(page);
}