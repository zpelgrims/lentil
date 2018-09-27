**@kaden:**

This is the folder I'd like you to push your work to. Please commit as much as you can, it doesn't need to be functional code, it can be your thoughts/findings in text as well. This way I will be able to somewhat keep track of it all.


------------



**Initial todo** *(feel free to modify)*:

- [x] Figure out the best initial path to take:
	- Using a pre-built platform: could be annoying to customize, but some features will be great out of the box
	- Building the whole thing from scratch: if the user model/payment model is relatively easy to add, this might be the best option since we don't need many other features.
	
	
- [x] Build the contents/products from a `.json` database
	- Products are various virtual lenses, they come with some info/images. We can think about how to display them later, for now just displaying them all would be great.
	- Public `.json` can be found [here](https://github.com/zpelgrims/lentil/blob/master/www/json/lenses_public.json), expect this file to be updated from time to time.
	

- [x] User model
	- Users need to register/login, their info & purchases need to be stored in a database
	- It should be clear on products/content page which ones they already own


- [ ] Add a filter function
	- [x] Filters based on company, product or year. These options can easily
	be changed
	- [ ] Filter based on company: provide checkboxes for the companies that you want to display
	- [ ] Year: from min to max
	- [ ] Focal length: from min to max

	
- [ ] Payment model
	- [x] Paypal is great, but it would be best to also support credit/debit cards since the primary target are studios, not necessarily individuals.
	- [x] Create a cart so people can do checkouts of multiple lenses at once
	- [x] Create cart page to display items added to cart before checkout


- [ ] Lens expansion on-click


- [x] Add ownership of lenses to user model after confirmed payment


- [ ] Migrate database to mlab


- [ ] Create basic front-end layout


- [ ] Add flash messages for UI
	
	
- [ ] The plugin compile needs to be triggered on-demand by the user.
	- Because we need to include only (all) the lenses they purchased. 
	- This will involve passing a list of the purchased lenses to a Makefile, which needs to be executed in a terminal. Then the whole thing needs to be uploaded and passed as a download link to the user.
	- Essentially.. figure out how to trigger a command in the terminal from the webpage.
	
	
- [x] Avoid having to manually add new lens entries. The lenses will most likely be updated along the way and it will be a mess to manage all that. But since we're already loading the content from the database, this shouldn't be a big issue.

	
- [ ] Eventually setup the hosting/domain. I've got good experiences with [digitalocean](https://www.digitalocean.com "digitalocean.com"), hopefully we can host it there. But that's for a long way down the line.