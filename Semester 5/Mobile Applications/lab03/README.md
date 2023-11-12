A list/recycler view is used linked to a view model/repository class/component. The activity/fragment/component is marshaling only the affected object/operation. No rebuild of the list/adapter or activity/fragment/component.

﻿Only the created element is added in the list. The create operation is maintained is a separate activity/fragment/component. All the main fields are available to be set. The create view/form has labels for each input field. If we have validation errors the errors are handled in this view.

﻿Only the updated element is passed back to the list. The element is properly identified. The update operation is maintained in a separate activity/fragment/component. All the main fields are available to be updated. The update view/form has labels for each input field and the existing values are pre-populated. If we have validation errors the errors are handled in this view.

﻿Only the id of the removed element is passed back to the list. The element is properly identified. A confirmation dialog is used.
