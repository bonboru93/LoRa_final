package com.example.bonboru.sosolr;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;



public class MessageActivity extends AppCompatActivity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_message);
        Toast.makeText(this, "Now you can contact with SOS center.", Toast.LENGTH_SHORT).show();

    }
}
