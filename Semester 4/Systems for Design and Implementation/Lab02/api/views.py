from django_filters.rest_framework import DjangoFilterBackend

from rest_framework import generics, filters

from api.models import NutritionFactsPerScoop, ProteinPowder, MonohydrateCreatinePowder
from api.serializers import NutritionFactsPerScoopSerializer, ProteinPowderSerializer, MonohydrateCreatinePowderSerializer, NutritionFactsPerScoopListSerializer, ProteinPowderListSerializer, MonohydrateCreatinePowderListSerializer

# Create your views here.
class NutritionFactsPerScoopList(generics.ListCreateAPIView):
    serializer_class = NutritionFactsPerScoopListSerializer
    queryset = NutritionFactsPerScoop.objects.all()

    filter_backends = [DjangoFilterBackend, filters.SearchFilter, filters.OrderingFilter]
    filterset_fields = {'quantity_in_grams': ['gte', 'lte'], 
                        'calories': ['gte', 'lte'], 
                        'protein': ['gte', 'lte', 'exact'], 
                        }
    ordering_fields = ['quantity_in_grams', 'calories', 'protein']

class NutritionFactsPerScoopDetails(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = NutritionFactsPerScoopSerializer
    queryset = NutritionFactsPerScoop.objects.all()


class ProteinPowderList(generics.ListCreateAPIView):
    serializer_class = ProteinPowderListSerializer

    filter_backends = [DjangoFilterBackend, filters.SearchFilter, filters.OrderingFilter]
    filterset_fields = {'price': ['gte', 'lte'], 
                        'quantity_in_grams': ['gte', 'lte'],
                        'protein_name': ['icontains'],
                        'producer_name': ['icontains'], 
                        'flavour': ['icontains'], 
                        'is_vegan': ['exact']
                        }
    search_fields = ['$protein_name', '$producer_name', '$flavour']
    ordering_fields = ['price', 'quantity_in_grams']

    def get_queryset(self):
        queryset = ProteinPowder.objects.all()
        scoop = self.request.query_params.get('protein-nutrition-facts')

        if scoop is not None:
            queryset = queryset.filter(scoop_nutrition_facts=scoop)

        return queryset

class ProteinPowderDetails(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = ProteinPowderSerializer
    queryset = ProteinPowder.objects.all()


class MonohydrateCreatinePowderList(generics.ListCreateAPIView):
    serializer_class = MonohydrateCreatinePowderListSerializer
    queryset = MonohydrateCreatinePowder.objects.all()

    filter_backends = [DjangoFilterBackend, filters.SearchFilter, filters.OrderingFilter]
    filterset_fields = {'price': ['gte', 'lte'], 
                        'producer_name': ['icontains'], 
                        'flavour': ['icontains'], 
                        'is_vegan': ['exact']
                        }
    search_fields = ['$producer_name', '$flavour']
    ordering_fields = ['price', 'quantity_in_grams']

class MonohydrateCreatinePowderDetails(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = MonohydrateCreatinePowderSerializer
    queryset = MonohydrateCreatinePowder.objects.all()
