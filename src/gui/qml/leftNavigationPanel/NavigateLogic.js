function switchPage(item, page, record = true) {
    if (item === navigationPanel.currentItem) {
        return
    }
    navigationPanel.currentItem = item
    mainSwitchPage(page)
    if (record === true) {
        window.commands.push(function () {
            switchPage(item, page, false)
        })
    }
}
