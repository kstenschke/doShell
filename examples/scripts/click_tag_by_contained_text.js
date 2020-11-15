var elements = document.getElementsByTagName('<tag_name>');
var searchText = '<search_text>';

for (var i = 0; i < elements.length; i++) {
    if (elements[i].textContent === searchText) {
        elements[i].click();
        break;
    }
}
