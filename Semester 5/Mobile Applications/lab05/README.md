Read operation:


All the values are retrieved only once and reused while the application is alive. 
A separate repository is used. A websocket is used to listen for server changes.



Create operation:


Only the created element is sent to the server. The id is managed by the server. The user is not aware of the internal id.



Update operation:


The server element is reused. 
Eg. the element is not deleted and then a new one is added. 
The id should remain the same.



Delete operation:


Only the id of the removed element is sent to the server. 
The element is properly identified. If we have persistence/network errors the messages are logged and presented to the user.



Separate thread/coroutine:
All server operations are handled in a separate thread/coroutine.



Error/Validation messages:


If there are error the application should present them to the user in a friendly manner. No raw messages should be presented.



Client debug logs:


All client operations are having debug logs.



Server logs:


All server operations are having debug logs.




Server integration:
- Iterate on the DB project to implement the server support.
- All the CRUD operations should retrieve/send from/to a remote server and fall back to the local DB if the Internet connection is down.
- You should be able to demo all CRUD operations, using your own REST server (No cloud services are allowed).
