# Makefile (JASON YEOH)
#  'make rw' to run


restaurant_waitlist: restaurant_waitlist_ui.o restaurant_waitlist_ll.o restaurant_waitlist_ds.o
	gcc -o restaurant_waitlist restaurant_waitlist_ui.o restaurant_waitlist_ll.o restaurant_waitlist_ds.o

restaurant_waitlist_ui.o: restaurant_waitlist_ui.c restaurant_waitlist.h
	gcc -c restaurant_waitlist_ui.c

restaurant_waitlist_ll.o: restaurant_waitlist_ll.c restaurant_waitlist.h
	gcc -c restaurant_waitlist_ll.c

restaurant_waitlist_ds.o: restaurant_waitlist_ds.c restaurant_waitlist.h
	gcc -c restaurant_waitlist_ds.c

clean:
	rm restaurant_waitlist_ui.o restaurant_waitlist_ll.o restaurant_waitlist_ds.o restaurant_waitlist
