function switchPage(item,page){
    if(tabsBar.currentItem==item)
        return;
    tabsBar.currentItem=item;
    stackView.replace(page);
    window.commands.push(function(){
        switchPage(item,page);
    });
}