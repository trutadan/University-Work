use Rap;

-- there can't be a concert without any location
DELETE Rappers
	where fullName is NULL and dateOfBirth is NULL;


-- keep only popular songs
DELETE RapSongs
	where streams < 500000;