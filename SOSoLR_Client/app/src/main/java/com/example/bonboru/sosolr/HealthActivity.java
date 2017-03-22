package com.example.bonboru.sosolr;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;

import java.io.OutputStream;
import java.net.Socket;

class tcp_send implements Runnable
{

    @Override
    public void run() {
        try {
            Socket socket = new Socket("192.168.100.1", 50505);
            OutputStream outputStream = socket.getOutputStream();
            String str = "[SOSoLR],r,";
            str += Integer.toString(WelcomeActivity.welcomeActivity.id) + "," + WelcomeActivity.welcomeActivity.name + "," + WelcomeActivity.welcomeActivity.lat + ","  + WelcomeActivity.welcomeActivity.lon + ","
                    + Integer.toString(HealthActivity.healthActivity.item1) + "," + Integer.toString(HealthActivity.healthActivity.item2) + "," + Integer.toString(HealthActivity.healthActivity.item3) + "," + Integer.toString(HealthActivity.healthActivity.item4) + ",\n";
            outputStream.write(str.getBytes());
            outputStream.flush();
            socket.close();
            System.out.println(str);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

public class HealthActivity extends AppCompatActivity {

    public int item1, item2, item3, item4;
    public static HealthActivity healthActivity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_health);
        Toast.makeText(this, "Now please report your physical condition.", Toast.LENGTH_SHORT).show();

        healthActivity = this;

        String[] blood={"A","B","O","AB"};
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, blood);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        ((Spinner)findViewById(R.id.spinner2)).setAdapter(adapter);
        String[] yy={"Good","Pain","Bad"};
        ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, yy);
        adapter2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        String[] yy2={"Enough","Medium","None"};
        ArrayAdapter<String> adapter3 = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, yy2);
        adapter3.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        ((Spinner)findViewById(R.id.spinner3)).setAdapter(adapter2);
        ((Spinner)findViewById(R.id.spinner4)).setAdapter(adapter2);
        ((Spinner)findViewById(R.id.spinner5)).setAdapter(adapter3);
    }

    public void report(View view) {
        item1 = ((Spinner)findViewById(R.id.spinner2)).getSelectedItemPosition();
        item2 = ((Spinner)findViewById(R.id.spinner3)).getSelectedItemPosition();
        item3 = ((Spinner)findViewById(R.id.spinner4)).getSelectedItemPosition();
        item4 = ((Spinner)findViewById(R.id.spinner5)).getSelectedItemPosition();

        Thread t = new Thread(new tcp_send());
        t.start();

        startActivity(new Intent(HealthActivity.this, MessageActivity.class));
    }
}
