used to create [[SmartReference]] keeps track of how many exist
keeps track of whether the object it's managing still exists which can ask about
deletes self once tracked object no longer exists and no more references exist.
owner needs to tell it when it no longer exists