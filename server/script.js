
$(document).ready(function(){
  $("#CafeInstantRecette").click(function(){
    var box = $('#result');
    $.ajax({
      url: '/GetRecette',
      type: 'GET',
      dataType : 'text',
      success: function(response){

        box.html(response)
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
