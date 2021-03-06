### Deadlock recovery
Deadlock recovery deals with problems in case of deadlock.
The system may kill all the processes that participate
in the deadlock, which may not be acceptable for
obvious reasons (nobody wants to be killed).
Still may be acceptable for stateless devices,
such as microservice servers, embedded devices, etc.

### Deadlock prevention
Deadlock prevention takes time to check for possible
deadlock every time a resource is requested.
This may not be acceptable in real-time operating systems
as it takes precious clock cycles.
This may be acceptable for desktop systems
and other non-time sensitive systems.

### Deadlock avoidance
This may happen if some of conditions are not met,

 - Mutual-Exclusion: spooling resources and exposing
   a service in another process
 - Hold-And-Wait: make all resource requests beforehand
 - No-Preemtion: take the resource away from the process
 - Circular Wait: every process may be granted access to a resource with number that is greater than number of previously acquainted resources
