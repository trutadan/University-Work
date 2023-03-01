from rest_framework import generics

from api.models import NutritionFactsPerScoop, ProteinPowder
from api.serializers import NutritionFactsPerScoopSerializer, ProteinPowderSerializer

# Create your views here.
class NutritionFactsPerScoopList(generics.ListCreateAPIView):
    serializer_class = NutritionFactsPerScoopSerializer
    queryset = NutritionFactsPerScoop.objects.all()

class NutritionFactsPerScoopDetails(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = NutritionFactsPerScoopSerializer
    queryset = NutritionFactsPerScoop.objects.all()


class ProteinPowderList(generics.ListCreateAPIView):
    serializer_class = ProteinPowderSerializer

    def get_queryset(self):
        queryset = ProteinPowder.objects.all()
        scoop = self.request.query_params.get('protein-nutrition-facts')

        if scoop is not None:
            queryset = queryset.filter(scoop_nutrition_facts=scoop)

        return queryset

class ProteinPowderDetails(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = ProteinPowderSerializer
    queryset = ProteinPowder.objects.all()
