//.import "../../leftNavigationPanel/NavigateLogic.js" as Qualifier

function switchPage(item,page){
    if(tabsBar.currentItem==item)
        return;
    tabsBar.changeCurrentItem(item);
    stackView.replace(page);/*
    window.commands.push(function(){
        if(tabsBar.currentItem==item)
        switchPage(item,page);
    });
    */
}

