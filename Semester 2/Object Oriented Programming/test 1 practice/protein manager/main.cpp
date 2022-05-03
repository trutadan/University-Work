#include <iostream>
#include "UI.h"

/*void test_controller_remove(){

}

void test_controller_get_all_proteins_containing_given_sequence_sorted_by_name(){

}*/

void add_entries_at_startup(Controller &controller){
    controller.add_protein(Protein{"Human", "Myosin-2", "MSSDSELAVFGEAA"});
    controller.add_protein(Protein{"Human", "Keratin", "TGASDFSGRPERWTEO"});
    controller.add_protein(Protein{"Mouse", "Keratin", "MLWWEEVERTSFGSDGQKK"});
    controller.add_protein(Protein{"E-Coli", "tufA", "VTLIHPIAMDDGLRFAIRE"});
    controller.add_protein(Protein{"E-Coli", "cspE", "MSKIKGNVKWFNESKGFDFHDG"});
}

int main() {
/*    {
        test_controller_remove();
        test_controller_get_all_proteins_containing_given_sequence_sorted_by_name();
    }*/

    {
        Repository repository;
        Controller controller{repository};
        add_entries_at_startup(controller);
        UI ui{controller};

        ui.start_program();
    }

    return 0;
}
