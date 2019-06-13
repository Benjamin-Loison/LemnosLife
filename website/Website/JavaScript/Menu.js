function PopUp(hideOrshow)
{
	if(hideOrshow == 'hide')
	{
    	document.getElementById('ac-wrapper').style.display = "none";
    }
    else if(localStorage.getItem("popupWasShown") == null)
	{
        localStorage.setItem("popupWasShown", 1);
        document.getElementById('ac-wrapper').removeAttribute('style');
    }
}

function hideNow(e)
{
    if(e.target.id == 'ac-wrapper')
		document.getElementById('ac-wrapper').style.display = 'none';
}
