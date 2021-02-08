
$(document).ready(function(){
  $("#CafeInstantRecette").click(function(){
    var box = $('#result');
    $.ajax({
      url: '/GetRecette',
      type: 'GET',
      dataType : 'JSON',
      success: function(response){

        // box.html(response['Recette'][1]['nb_dose_cafe']);
        bow.html(response.json.array.length);
        // Recette(response)
        console.log(response);
      },
      error: function(error){
        box.html("error");
        console.log(error);

    }
    });
  });
});

// Recette(response) {
//   for (var i ; i < response.length)
//   document.getElementById("Recette").innerHTML = '<option value="Grand">Grand</option>';
// }
