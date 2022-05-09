#include "Tests/Tests.h"
#include "UI/UI.h"
#include "Functions/Functions.h"
#include <iostream>
#include <crtdbg.h>

void add_entries_at_startup(Controller& controller)
{
    controller.add_event_to_repository("Singles Party Charlie", "Vrei sa-ti faci noi prieteni; sa te bucuri de libertate si un orar fara restrictii; sa canti si sa dansezi?", Datetime{ 26,3,2022,7,30 }, 150, "https://www.clujlife.com/eveniment/singles-party-charlie/");
    controller.add_event_to_repository("CLOSER v.1", "With the departure process coming to an end; the rivers flow free through the melted barriers. It is time to return closer to the core", Datetime{ 1,3,2022,8,0 }, 25, "https://www.clujlife.com/eveniment/closer-v-1/");
    controller.add_event_to_repository("Retro gaming LAN Party", " O zi in care poti sa joci cateva jocuri video retro (pe console si PC) la noi in spatiu.", Datetime{ 3,4,2022,14,15 }, 206, "https://www.clujlife.com/eveniment/retro-gaming-lan-party-3/2022-04-03/");
    controller.add_event_to_repository("Fancy Garage Sale - 10th Edition", "Va invitam la o dupa - masa de targuiala vesela; un fel de OSER mai fancy cu articole atat vechi; cat si noi.", Datetime{ 3,4,2022,16,30 }, 27, "https://www.clujlife.com/eveniment/fancy-garage-sale-10th-edition-urania-palace/");
    controller.add_event_to_repository("Fools Comedy Days", "Se numeste 'Fools Comedy Days - Cluj' si dureaza 3 zile.", Datetime{ 15,5,2022,19,15 }, 206, "https ://www.clujlife.com/eveniment/fools-comedy-days-iulius-parc-cluj-napoca/");
    controller.add_event_to_repository("The INNER - Mapping inside", "Mappingx Inside este primul eveniment de invatare ai practica din Romania, dedicat starii de bine si sanatatii corp-minte-suflet.", Datetime{ 3,6,2022,15,30 }, 54, "https://www.clujlife.com/eveniment/the-inner-mapping-inside/");
    controller.add_event_to_repository("Jazz in the Park 2022", "In 1-4 septembrie 2022; ne revedem in Parcul Etnografic din Cluj-Napoca. Va fi jazz, asa ca ramai pe-aproape. Mai multe detalii in curand.", Datetime{ 1,9,2022,18,0 }, 452, "https://www.clujlife.com/eveniment/jazz-in-the-park-2022/");
    controller.add_event_to_repository("UNTOLD FESTIVAL 2022", "Together we will write a new chapter of the UNTOLD story! See you on the 4th of August 2022", Datetime{ 7,8,2022,10,0 }, 12254, "https://www.clujlife.com/eveniment/untold-festival-2022/");
    controller.add_event_to_repository("Electric Castle 2022", "Electric Castle is a one-of-a-kind music festival happening between July 13-17 2022; at Banffy Castle in Transylvania.", Datetime{ 13,7,2022,11,30 }, 5154, "https://www.clujlife.com/eveniment/electric-castle-2022/");
    controller.add_event_to_repository("Jimmy Carr - Live in Cluj", "Jimmy Carr pune Cluj-Napoca pe harta celui mai recent turneu de stand up comedy pe care l-a lansat - TERRIBLY FUNNY.", Datetime{ 1,10,2022,19,0 }, 74, "https://www.clujlife.com/eveniment/jimmy-carr-live-in-cluj/");
}

int main()
{
    system("Color 0A");

        {
        test_all_functionalities();
        }
        
        {
        Repository* list = new Repository;
        Repository* repository = new Repository;

        Controller controller{ repository, list };

        UI ui{ controller };

        ui.start_program();
        }

//    _CrtDumpMemoryLeaks();

    system("pause");
    return 0;
}
