from django.urls import path
from api.views import NutritionFactsPerScoopList, NutritionFactsPerScoopDetails, ProteinPowderList, ProteinPowderDetails, MonohydrateCreatinePowderList, MonohydrateCreatinePowderDetails

urlpatterns = [
    path('protein-nutrition-facts/', NutritionFactsPerScoopList.as_view()),
    path('protein-nutrition-facts/<int:pk>/', NutritionFactsPerScoopDetails.as_view()),
    path('protein-powder/', ProteinPowderList.as_view()),
    path('protein-powder/<int:pk>/', ProteinPowderDetails.as_view()),
    path('monohydrate-creatine-powder/', MonohydrateCreatinePowderList.as_view()),
    path('monohydrate-creatine-powder/<int:pk>/', MonohydrateCreatinePowderDetails.as_view())
]