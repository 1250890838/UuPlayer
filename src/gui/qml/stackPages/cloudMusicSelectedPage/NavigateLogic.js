function switchPage(item){
    if(tabsBar.currentItem==item)
        return;
    stackView.push(item);
}