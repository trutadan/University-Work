from ui.ui import UI
from repository.repository import ShipRepository
from services.services import TableServices
from settings.constants import PLAYER, COMPUTER

if __name__ == '__main__':
    player_ship_repository = ShipRepository()
    computer_ship_repository = ShipRepository()

    player_table_services = TableServices(PLAYER, ship_repository=player_ship_repository)
    computer_table_services = TableServices(COMPUTER, ship_repository=computer_ship_repository)

    console = UI(player_table_services, computer_table_services)
    console.run_game()
