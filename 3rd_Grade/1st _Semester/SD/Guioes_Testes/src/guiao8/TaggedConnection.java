package guiao8;

import java.io.*;
import java.net.Socket;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class TaggedConnection implements AutoCloseable {
    private final Socket socket;
    private final DataInputStream in;
    private final DataOutputStream out;
    private final Lock rlock;
    private final Lock wlock;

    public static class Frame {
        public final int tag;
        public final byte[] data;

        public Frame(int tag, byte[] data) {
            this.tag = tag;
            this.data = data;
        }
    }

    public TaggedConnection(Socket socket) throws IOException {
        this.socket = socket;
        this.in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
        this.out = new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
        this.rlock = new ReentrantLock();
        this.wlock = new ReentrantLock();
    }

    public void send(Frame frame) throws IOException {
        wlock.lock();
        this.out.writeInt(frame.tag);
        this.out.writeInt(frame.data.length);
        this.out.write(frame.data);
        this.out.flush();
        wlock.unlock();
    }

    public void send(int tag, byte[] data) throws IOException {
        this.send(new Frame(tag,data));
    }

    public Frame receive() throws IOException {
        rlock.lock();
        int tag = 0;
        int size = 0;
        tag = in.readInt();
        size = in.readInt();
        byte[] data = new byte[size];
        in.readFully(data);
        rlock.unlock();
        return new Frame(tag,data);
    }

    public void close() throws IOException {
        this.out.close();
        this.in.close();
    }
}
