myPix = new Array("1.png", "2.png","3.png","4.png","5.png","6.png","7.png","8.png","9.png","10.png","11.png","12.png","13.png","14.png","15.png","16.png","17.png","18.png","19.png","20.png","21.png")

speed = 3500; i = 0; function autoSlideShow(imgname) {
  if (document.images)
  {
    document.getElementById(imgname).src = 'Website/Media/Pictures/' + myPix[i];
    i++;
    if (i > myPix.length-1) i = 0;
    b=imgname;
    objet_timer = setTimeout('autoSlideShow(b)',speed);
  }
}

function preload(myPix) {
  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
  var i,j=d.MM_p.length,a=preload.arguments; for(i=0; i<a.length; i++)
  if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; 
d.MM_p[j++].src=a[i];}}
}
