# OOP_Assignment3
A knock on your chamber door interrupts your nightly study session. Upon opening it, all you find is a superficially bound parchment, its sides singed and flame licked. You open it on your study and peruse it, to discover that it was written by an armorer from the town's periphery. He has sent a courier to deliver a half-desperate plea for help to the Spire. A transport carrying weapons, armor and some interesting trinkets has just arrived this morning at his doorstep and an inspection from the local higher-ups is due the next day. He thought giving the Mage Guild a chance to help could pay off, if anyone would be able to help lift and compartmentalize his new and very cumbersome wares. Along with this, the incantation should also be able to point out specific pieces of heavy armor for retrieval from the store room and automatically dispose of faulty bits of gear.
A small reward would be conveyed to whomever would get the job done, together with a bigger, symbolic one - the armorer gives his word that, should this succeed, he will put in a good word with every metalworker, blacksmith or heavy wares trader he knows in town regarding magic users and their craft.
The quartermaster must be able to add, modify and dispose of gear. He must also be able to see all gear, and only the gear of a certain type. All incantations must be spoken in the form:
add catalogueNumber, state, type, value
update catalogueNumber, newState, newType, newValue
delete catalogueNumber
list
list type
The space on the shelves should remain static as it is. No need to change shelf size depending on the number of items stored. (static memory allocation)
You need to use multiple tablets to keep your incantations on. (domain, repository, controller, UI in different modules)
If the quartermaster tries to re-add the same item or delete a non-existing one the incantation must say "No!".
Example test run:
add 123, abc, def, 456
list
exit
Expected output: (formating is ignored)
[possibly some text here]123[possibly some text here]abc[possibly some text here]def[possibly some text here]456[possibly some text here]
