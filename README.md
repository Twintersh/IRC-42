# Insane_Radioactive_Capybara
IRC c++ project


## TODO

- [x] Server properties:
	- [x] CLIENT LIST
	- [x] CHANNEL LIST

- [x] Client properties :
	- [x] USERNAME
	- [x] NICKNAME
	- [x] RIGHTS
	- [x] JOINED CHANNELS

- [x] Channel properties :
	- [x] TOPIC
	- [x] OPERATORS TOPIC RESTRICTIONS
	- [x] USER LIMIT
	- [x] INVITE-ONLY MODE
	- [x] PASSWORD
	- [x] CLIENT / OPERATORS LIST

- [x] Client commands :
	- [x] PASS
	- [ ] NICK
	- [x] USER
	- [x] JOIN
	- [x] PART
	- [x] PRVMSG // missing missing argument check

- [ ] Channel operator commands :
	- [ ] KICK
	- [ ] INVITE
	- [ ] TOPIC
	- [ ] MODE
		- i: change invite only mode
		- t: change or remove operator Topic command rights
		- k: change or remove channel password
		- o: give or take operator rights
		- l: change user limit
