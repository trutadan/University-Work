from django.urls import path
from api.views import NutritionFactsPerScoopList, NutritionFactsPerScoopDetails, ProteinPowderList, ProteinPowderDetails

urlpatterns = [
    path('protein-nutrition-facts/', NutritionFactsPerScoopList.as_view()),
    path('protein-nutrition-facts/<int:pk>/', NutritionFactsPerScoopDetails.as_view()),
    path('protein-powder/', ProteinPowderList.as_view()),
    path('protein-powder/<int:pk>/', ProteinPowderDetails.as_view())
]