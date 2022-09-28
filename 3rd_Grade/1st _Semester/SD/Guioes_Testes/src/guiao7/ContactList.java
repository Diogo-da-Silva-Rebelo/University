package guiao7;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;

class ContactList extends ArrayList<Contact> {

    // @TODO
    public void serialize (DataOutputStream out) throws IOException {
        out.writeInt(this.size());

        for(Contact c : this){
            c.serialize(out);
        }
    }

    // @TODO
    public static ContactList deserialize (DataInputStream in) throws IOException {
        ContactList contactL = new ContactList();

        for(int i = 0; i < in.readInt(); i++){
            contactL.add(Contact.deserialize(in));
        }
        return contactL;
    }
}
