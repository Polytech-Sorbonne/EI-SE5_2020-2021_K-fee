
$(document).ready(function(){
  $("#CafeInstantRecette").click(function(){
    var box = $('#result');
    $.ajax({
      url: '/GetRecette',
      type: 'GET',
      dataType : 'JSON',
      success: function(response){

        box.html(response.id[0]);
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
