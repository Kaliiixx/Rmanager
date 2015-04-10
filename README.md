# Rmanager
==========

Rmanager is divided into two main parts :
* Items catalog
* Funds management

## Command Line interface
The command line interface is written in C.

## Graphical user interface 
(see [Riinka's project](https://github.com/Riinka/Rmanager-gui))

##Manual

	rmanager help [COMMAND] -- display help
	rmanager add CATEGORIE-- add an element to the database
	rmanager del FILENUMBER -- delete the element associated to FILENUMBER from the database
	rmanager import FILE CATEGORIE -- import an element to one categorie of the database
	rmanager config -- open the configuration prompt
	rmanager create MODEL -- create a new categorie.
	
	
###Specifications
The program is splitted into three parts for three actors :
* Item manager
* User
* Treasurer

#### To do
##### Priorities
* Books management
	* loans
	* giving back
	* loan renwals
	* reservations
	* latenesses

* Periodical management

* Catalog

* User management
	* User lists creation

* Acquisitions management
	* budget management
	* baskets
	* claimings

####Secondary
* Users can read and add comments to an item
* The Database run with multi site transfers
* Statistic reports about items with preferences

