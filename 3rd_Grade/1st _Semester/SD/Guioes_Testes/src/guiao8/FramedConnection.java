package guiao8;

import java.io.*;
import java.net.Socket;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class FramedConnection implements AutoCloseable {
    private final DataInputStream in;
    private final DataOutputStream out;
    private final Lock rlock;
    private final Lock wlock;

    public FramedConnection(Socket socket) throws IOException {
        this.in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
        this.out = new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
        this.rlock = new ReentrantLock();
        this.wlock = new ReentrantLock();
    }
    public void send(byte[] data) throws IOException {
        wlock.lock();
        this.out.writeInt(data.length);
        this.out.write(data);
        this.out.flush();
        wlock.unlock();
    }
    public byte[] receive() throws IOException {
        rlock.lock();
        int size = 0;
        size = in.readInt();
        byte[] data = new byte[size];
        in.readFully(data);
        rlock.unlock();
        return data;
    }
    public void close() throws IOException {
        in.close();
        out.close();
    }
}