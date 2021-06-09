class Photo	{
    String id;


    Photo(String id) {
        this.id	= id;
    }

    public String toString() {
        return this.id;
    }
}

public class PhotoAlbum {

    private class PhotoNode {
        Photo photo;
        PhotoNode next;
        PhotoNode prev;
    }

    private int pos;
    private int count;
    private PhotoNode current;

    public PhotoAlbum() {
        this.pos = 0;
        this.count = 0;
        this.current = null;
    }

    public Photo insert(Photo photo) {
        PhotoNode node = new PhotoNode();
        node.photo = photo;
        node.next = this.current;
        if (this.current != null) {
            node.prev = this.current.prev;
        } else {
            node.prev = null;
        }

        if (this.current != null && this.current.prev != null) {
            this.current.prev.next = node;
            this.current.prev = node;
        }
        this.current = node;

        count++;
        return photo;
    }

    public Photo current() {
        return current.photo;
    }

    public Photo next() {
        if (count < pos) {
            this.current = current.next;
            pos++;
            return this.current.photo;
        } else {
            return null;
        }
    }

    public Photo prev() {
        if (pos > 0) {
            this.current = current.prev;
            pos--;
            return this.current.photo;
        } else {
            return null;
        }
    }

    public void delete() {
        if (this.current != null) {
            if (this.current.prev != null)
                this.current.prev.next = this.current.next;

            if (this.current.next != null)
                this.current.next.prev = this.current.prev;

            this.current = this.current.next;
        }

        count--;
    }
}