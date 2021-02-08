
$(document).ready(function(){
  $("#CafeInstantRecette").click(function(){
    var box = $('#result');
    $.ajax({
      url: '/GetRecette',
      type: 'GET',
      dataType : 'JSON',
      success: function(response){

        box.html(response.id);
        //Recette(response)
        console.log(response);
      },
      error: function(error){
        box.html("error");
        console.log(error);

    }
    });
  });
});

function activeNouveauCafe() {
  var div = document.getElementById("NouveauCafe");
  if (div.style.display == "none"){
    div.style.display = "block";
  }
  else{
    div.style.display = "none";
  }
}

function activeCafeRecette() {
var div = document.getElementById("CafeRecette");
if (div.style.display == "none"){
  div.style.display = "block";
}
else{
  div.style.display = "none";
}
}
