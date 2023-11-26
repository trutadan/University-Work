Read operation is implemented in a list:
All the values are retrieved only once and reused while the application is alive. A separate repository is used. The values are retrieved in a separate thread/coroutine. An observer/liveData mechanism is used to listen for changes. If we have retrieve errors the messages are handled in this view, presented to the user and logged.


Create operation:
Only the created element is added in the db. The id is managed by the db/app. The user is not aware of the internal id.If we have persistence errors the messages are handled in this view, presented to the user and logged.


Update operation:
The db element is reused. Eg. the element is not deleted and then a new one is added. The id should remain the same. If we have persistence errors the messages are handled in this view, presented to the user and logged.


Delete operation:
Only the id of the removed element is used to delete. The element is properly identified. If we have persistence errors the messages are logged and presented to the user.
