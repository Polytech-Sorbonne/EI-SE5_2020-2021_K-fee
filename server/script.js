
$.ajax({
  url: '/GetRecette',
  type: 'GET',
  dataType : 'JSON',
  success: function(response){
    Recette(response)
    console.log(response);
  },
  error: function(error){
    box.html("error");
    console.log(error);

}
});


function Recette(response) {
  var box = $('#result');

  for (var i = 0; i < response["Recette"].length ; i++) {

    var optionRecette = '<option value=' + response["Recette"][i]['nom'] + '>' + response["Recette"][i]['nom']+ '</option>';
    document.getElementById("ajoutSelect").innerHTML += optionRecette;
  }

  for (var i = 0; i < response["Recette"].length ; i++) {

      var chaine = "<div id = "+response["Recette"][i]["nom"] + " style='display:none;'> " ;
      chaine += "<ul> <li> Nombre de dose de café : " + response["Recette"][i]['nb_dose_cafe']+ '</li>';
      chaine += "<li>Nombre de sucre : " + response["Recette"][i]['nb_dose_sucre']+ '</li>';
      chaine += "<li>Taille : " + response["Recette"][i]['taille']+ '</li>';
      chaine += "<li>Température : " + response["Recette"][i]['temperature']+ '</li></ul></div>';
      document.getElementById("result").innerHTML += chaine;


  }
}

function AfficheRecette() {
  var selectElmt = document.getElementById("ajoutSelect");
  var valeurselectionnee = selectElmt.options[selectElmt.selectedIndex].value;

  for ( var v = 1 ; v < selectElmt.length; v++) {

    var valeur = selectElmt.options[v].value;
    var div = document.getElementById(valeur)


    if ( valeur == valeurselectionnee) {
      if (div.style.display == "none") {
        div.style.display = "block";
      }
    }
    else if  (div.style.display == "block") {
      div.style.display = "none";
    }
  }

}
