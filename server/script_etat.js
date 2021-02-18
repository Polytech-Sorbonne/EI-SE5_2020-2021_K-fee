$.ajax({
  url: '/GetEtat',
  type: 'GET',
  dataType : 'JSON',
  success: function(response){
    console.log(response);
    Etat(response);

  },
  error: function(error){
    box.html("error");
    console.log(error);

}
});

//

function Etat(response){
//   value =

  var CafeJ = '<dd> <span> ' + response["Cafe"] + '% </span> <meter id ="jaugeCafe" value =' + response["Cafe"] + ' min = "0" max = "100" low = "10" >' ;
  document.getElementById("jaugeCafe").innerHTML += CafeJ;

  var SucreJ = '<dd> <span> ' + response["Sucre"] + '% </span> <meter id ="jaugeSucre" value =' + response["Sucre"] + ' min = "0" max = "100" low = "10" >' ;
  document.getElementById("jaugeSucre").innerHTML += SucreJ;

  var EauJ = '<dd> <span> ' + response["Eau"] + '% </span> <meter id ="jaugeSucre" value =' + response["Eau"] + ' min = "0" max = "100" low = "30" >' ;
  document.getElementById("jaugeEau").innerHTML += EauJ;

  if (response["Tasse"] == 1) {
    var Tasse = ' <img class="w3-image" src="https://www.cuisineaddict.com/8369-product_default/tasse-a-cafe-double-paroi-30cl-bistro-bodum-x2.jpg" width="200" height="200"></img>';
    document.getElementById("tasse").innerHTML += Tasse;
    var smiley = '<h3 class="w3-border-bottom w3-border-light-grey w3-padding-16"> <span style="front-size : 40px;"> &#x1F642;</span> Présence de la tasse</h3>'
    document.getElementById("smiley").innerHTML += smiley;
  }
  else {
    //
    var Tasse = ' <img class="w3-image" src="http://www.pur-cafe.com/blog/wp-includes/images/cafe_interdit.gif" width="200" height="200"></img>';
    document.getElementById("tasse").innerHTML += Tasse;
    var smiley = '<h3 class="w3-border-bottom w3-border-light-grey w3-padding-16"> <span style="front-size : 40px;"> &#x1F641;</span> Présence de la tasse</h3>'
    document.getElementById("smiley").innerHTML += smiley;
  }
}
