#include "GUI.h"
#include <QtWidgets/QApplication>

void add_entries_at_startup(Controller& controller)
{
    controller.add_event_to_repository("Singles Party Charlie", "Vrei sa-ti faci noi prieteni; sa te bucuri de libertate si un orar fara restrictii; sa canti si sa dansezi? Party!", Datetime{ 2022, 3, 26, 7, 30 }, 150, "www.clujlife.com/eveniment/singles-party-charlie/");
    controller.add_event_to_repository("CLOSER v.1", "With the departure process coming to an end; the rivers flow free through the melted barriers. It is time to return closer to the core", Datetime{ 2022, 3, 1, 8, 0 }, 25, "www.clujlife.com/eveniment/closer-v-1/");
    controller.add_event_to_repository("Retro Gaming LAN Party", " O zi plina de Gaming in care poti sa joci cateva jocuri video retro (pe console si PC) la noi in spatiu.", Datetime{ 2022, 4, 3, 14, 15 }, 206, "www.clujlife.com/eveniment/retro-gaming-lan-party-3/2022-04-03/");
    controller.add_event_to_repository("Fancy Garage Sale - 10th Edition", "Va invitam la o dupa - masa de targuiala vesela; un fel de OSER mai fancy cu articole atat vechi; cat si noi.", Datetime{ 2022, 4, 3, 16, 30 }, 27, "www.clujlife.com/eveniment/fancy-garage-sale-10th-edition-urania-palace/");
    controller.add_event_to_repository("Fools Comedy Days", "Se numeste 'Fools Comedy Days - Cluj' si dureaza 3 zile.", Datetime{ 2022, 5, 15, 19, 15 }, 206, "www.clujlife.com/eveniment/fools-comedy-days-iulius-parc-cluj-napoca/");
    controller.add_event_to_repository("The INNER - Mapping inside", "Mappingx Inside este primul eveniment de invatare ai practica din Romania; dedicat starii de bine si sanatatii corp-minte-suflet.", Datetime{ 2022, 6, 3,15,30 }, 54, "www.clujlife.com/eveniment/the-inner-mapping-inside/");
    controller.add_event_to_repository("Jazz in the Park 2022", "In 1-4 septembrie 2022; ne revedem in Parcul Etnografic din Cluj-Napoca. Va fi jazz; asa ca ramai pe-aproape. Mai multe detalii in curand.", Datetime{ 2022, 9, 1, 18,0 }, 452, "www.clujlife.com/eveniment/jazz-in-the-park-2022/");
    controller.add_event_to_repository("UNTOLD Festival 2022", "Together we will write a new chapter of the UNTOLD story Festival! See you on the 4th of August 2022", Datetime{ 2022, 8, 7, 10, 0 }, 1225, "www.clujlife.com/eveniment/untold-festival-2022/");
    controller.add_event_to_repository("Electric Castle Festival 2022", "Electric Castle is a one-of-a-kind music Festival happening between July 13-17 2022; at Banffy Castle in Transylvania.", Datetime{ 2022, 7, 13, 11, 30 }, 732, "www.clujlife.com/eveniment/electric-castle-2022/");
    controller.add_event_to_repository("Jimmy Carr - Live in Cluj", "Jimmy Carr pune Cluj-Napoca pe harta celui mai recent turneu de stand up Comedy pe care l-a lansat - TERRIBLY FUNNY.", Datetime{ 2022, 10, 1, 19, 0 }, 74, "www.clujlife.com/eveniment/jimmy-carr-live-in-cluj/");
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Repository* repository = new Repository();
    Repository* list = new Repository();

    Controller controller{ repository, list };
    add_entries_at_startup(controller);

    GUI gui(controller);
    gui.show();

    return a.exec();
}
