
$.ajax({
  url: '/GetRoutine',
  type: 'GET',
  dataType : 'JSON',
  success: function(response){
    Routine(response)
    console.log(response);
  },
  error: function(error){
    box.html("error");
    console.log(error);

}
});
//
// $.ajax({
//   url: '/GetRecette',
//   type: 'GET',
//   dataType : 'JSON',
//   success: function(response){
//     Recette(response)
//     console.log(response);
//   },
//   error: function(error){
//     box.html("error");
//     console.log(error);
//
// }
// });
//

function Routine(response) {
  var box = $('#result');

  for (var i = 0; i < response["Routine"].length ; i++) {

    var optionRoutine = '<option value=' + response["Routine"][i]['nom'] + '>' + response["Routine"][i]['nom']+ '</option>';
    document.getElementById("ShowRoutine").innerHTML += optionRoutine;
  }

  // for (var i = 0; i < response["Routine"].length ; i++) {
  //
  //     var chaine = "<div id = "+response["Routine"][i]["nom"] + " style='display:none;'> " ;
  //     chaine += "<ul> <li> Nombre de dose de café : " + response["Routine"][i]['nb_dose_cafe']+ '</li>';
  //     chaine += "<li>Température : " + response["Routine"][i]['temperature']+ '</li></ul></div>';
  //     document.getElementById("result").innerHTML += chaine;
  //
  //
  // }
}

// function AfficheRoutine() {
//   var selectElmt = document.getElementById("ShowRoutine");
//   var valeurselectionnee = selectElmt.options[selectElmt.selectedIndex].value;
//
//   for ( var v = 1 ; v < selectElmt.length; v++) {
//
//     var valeur = selectElmt.options[v].value;
//     var div = document.getElementById(valeur)
//
//
//     if ( valeur == valeurselectionnee) {
//       if (div.style.display == "none") {
//         div.style.display = "block";
//       }
//     }
//     else if  (div.style.display == "block") {
//       div.style.display = "none";
//     }
//   }
//
// }

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
  //var box = $('#result');

  for (var i = 0; i < response["Recette"].length ; i++) {

    var optionRecette = '<option value=' + response["Recette"][i]['nom'] + '>' + response["Recette"][i]['nom']+ '</option>';
    document.getElementById("ajoutRecetteLundi").innerHTML += optionRecette;
    document.getElementById("ajoutRecetteMardi").innerHTML += optionRecette;
    document.getElementById("ajoutRecetteMercredi").innerHTML += optionRecette;
    document.getElementById("ajoutRecetteJeudi").innerHTML += optionRecette;
    document.getElementById("ajoutRecetteVendredi").innerHTML += optionRecette;
    document.getElementById("ajoutRecetteSamedi").innerHTML += optionRecette;
    document.getElementById("ajoutRecetteDimanche").innerHTML += optionRecette;

  }


  for (var i = 0; i < response["Recette"].length ; i++) {

      var chaine = "<div id = "+response["Recette"][i]["nom"] + " style='display:none;'> " ;
      chaine += "<ul> <li> Nombre de dose de café : " + response["Recette"][i]['nb_dose_cafe']+ '</li>';
      chaine += "<li>Nombre de sucre : " + response["Recette"][i]['nb_dose_sucre']+ '</li>';
      chaine += "<li>Taille : " + response["Recette"][i]['taille']+ '</li>';
      chaine += "<li>Température : " + response["Recette"][i]['temperature']+ '</li></ul></div>';
      document.getElementById("RecetteLundi").innerHTML += chaine;
      document.getElementById("RecetteMardi").innerHTML += chaine;
      document.getElementById("RecetteMercredi").innerHTML += chaine;
      document.getElementById("RecetteJeudi").innerHTML += chaine;
      document.getElementById("RecetteVendredi").innerHTML += chaine;
      document.getElementById("RecetteSamedi").innerHTML += chaine;
      document.getElementById("RecetteDimanche").innerHTML += chaine;
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


function activeLundi() {
    var checkBox = document.getElementById("checkLundi");
    var div = document.getElementById("Lundi");
    var hour = document.getElementById("heure_Lundi");
    if (checkBox.checked == true){
        checkBox.value="lundi";
        div.style.display = "block";
        hour.required= true;
    }
    else{
        checkBox.value="uncheck";
        div.style.display = "none";
        hour.required = false;
    }
}

function activeMardi() {
    var checkBox = document.getElementById("checkMardi");
    var div = document.getElementById("Mardi");
    var hour = document.getElementById("heure_Mardi");
    if (checkBox.checked == true){
        checkBox.value="Mardi";
        div.style.display = "block";
        hour.required = true;
    }
    else{
        checkBox.value="uncheck";
        div.style.display = "none";
        hour.required = false;
    }
}

function activeMercredi() {
    var checkBox = document.getElementById("checkMercredi");
    var div = document.getElementById("Mercredi");
    var hour = document.getElementById("heure_Mercredi");
    if (checkBox.checked == true){
        checkBox.value="Mercredi";
        div.style.display = "block";
        hour.required = true;
    }
    else{
        checkBox.value="uncheck";
        div.style.display = "none";
        hour.required = false;
    }
}

function activeJeudi() {
    var checkBox = document.getElementById("checkJeudi");
    var div = document.getElementById("Jeudi");
    var hour = document.getElementById("heure_Jeudi");
    if (checkBox.checked == true){
        checkBox.value="Jeudi";
        div.style.display = "block";
        hour.required = true;
    }
    else{
        checkBox.value="uncheck";
        div.style.display = "none";
        hour.required = false;
    }
}

function activeVendredi() {
    var checkBox = document.getElementById("checkVendredi");
    var div = document.getElementById("Vendredi");
    var hour = document.getElementById("heure_Vendredi");
    if (checkBox.checked == true){
        checkBox.value="Vendredi";
        div.style.display = "block";
        hour.required = true;
    }
    else{
        checkBox.value="uncheck";
        div.style.display = "none";
        hour.required = false;
    }
}

function activeSamedi() {
    var checkBox = document.getElementById("checkSamedi");
    var div = document.getElementById("Samedi");
    var hour = document.getElementById("heure_Samedi");
    if (checkBox.checked == true){
        checkBox.value="Samedi";
        div.style.display = "block";
        hour.required = true;
    }
    else{
        checkBox.value="uncheck";
        div.style.display = "none";
        hour.required = false;
    }
}

function activeDimanche() {
    var checkBox = document.getElementById("checkDimanche");
    var div = document.getElementById("Dimanche");
    var hour = document.getElementById("heure_Dimanche");
    if (checkBox.checked == true){
        checkBox.value="Dimanche";
        div.style.display = "block";
        hour.required = true;
    }
    else{
        checkBox.value="uncheck";
        div.style.display = "none";
        hour.required = false;
    }

}

