**@kaden:**

This is the folder I'd like you to push your work to. Please commit as much as you can, it doesn't need to be functional code, it can be your thoughts/findings in text as well. This way I will be able to somewhat keep track of it all.


---



**BACK END TODO** *(feel free to modify)*:

- [x] Figure out the best initial path to take:
	- Using a pre-built platform: could be annoying to customize, but some features will be great out of the box
	- Building the whole thing from scratch: if the user model/payment model is relatively easy to add, this might be the best option since we don't need many other features.
	
	
- [x] Build the contents/products from a `.json` database
	- Products are various virtual lenses, they come with some info/images. We can think about how to display them later, for now just displaying them all would be great.
	- Public `.json` can be found [here](https://github.com/zpelgrims/lentil/blob/master/www/json/lenses_public.json), expect this file to be updated from time to time.
	

- [x] User model
	- Users need to register/login, their info & purchases need to be stored in a database
	- It should be clear on products/content page which ones they already own


- [x] Add a filter function
	- [x] Filters based on company, product or year. These options can easily
	be changed
	- [x] Filter based on company: provide checkboxes for the companies that you want to display
	- [x] Year: from min to max
	- [x] Focal length: from min to max
	- [x] Allow for multiple filter queries at once
	- [ ] Remember the filter options when the page reloads

	
- [x] Payment model
	- [x] Paypal is great, but it would be best to also support credit/debit cards since the primary target are studios, not necessarily individuals.
	- [x] Create a cart so people can do checkouts of multiple lenses at once
	- [x] Create cart page to display items added to cart before checkout
	- [x] Fix bug to display multiple items in cart


- [x] Lens expansion on-click


- [x] Add ownership of lenses to user model after confirmed payment


- [x] Migrate database to mlab


- [x] Add flash messages for UI

- [ ] Add more middleware
	- [x] Must not be able to add the same lens to cart more than once
	- [x] Must not add lens to cart if user already owns it
	- [ ] 

- [x] Remove pay page and simply run through checkout button with 
payment popup.	

- [x] Display ownership icons dynamically

- [ ] Make git version log dynamic

- [x] Allow user to remove an item from cart
	
- [ ] The plugin compile needs to be triggered on-demand by the user.
	- Because we need to include only (all) the lenses they purchased. 
	- Need to pass a command to the build server.
		- create a connection (ssh?), ssh keys will need to be stored so the connection is automatic and doesn't need human validation. Not sure about the security impacts of this? There must be a go-to way to do this, i just don't know it
		- pass the command (something like: `. ./build_server.sh username_string lens_string`)
		- command will return a location on the webserver (zeno will sync the final .zip file to the webserver in the buildscript)
	- Extra difficulty will be that there are 3 cases (linux, macOS, windows) and windows server will be hardest to interact with
	- maybe use this module? Not sure, just a suggestion
		- https://www.npmjs.com/package/node-cmd 
	
	
- [x] Avoid having to manually add new lens entries. The lenses will most likely be updated along the way and it will be a mess to manage all that. But since we're already loading the content from the database, this shouldn't be a big issue.
	
- [ ] Eventually setup the hosting/domain. I'd like to host it on vultr.com since that's where the build servers will be hosted as well.

---

**FRONT END TODO** *(feel free to modify)*:


- [x] Create basic front-end layout
- [x] Create nice looking filter/sort menu
- [x] Fix comparison images not loading intially
- [x] Text in general can be smaller in size
- [x] Reduce how much the lenses move up when clicked (probs about half of what we have now)
- [x] Hardcode git version log section
- [x] Add minimal animations
- [x] Restyle info section of expanded lens card
- [x] Setup image slider to have 4 images
- [x] Begin styling cart page
- [x] Add icons to lenses to mark ownership
- [x] Add icons to lenses to mark being in cart
- [ ] Add icons for new lenses
- [ ] Underline current page in navbar