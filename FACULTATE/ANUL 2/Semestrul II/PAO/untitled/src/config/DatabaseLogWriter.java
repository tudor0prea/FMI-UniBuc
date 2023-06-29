package config;

import java.io.*;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.util.Date;

public class DatabaseLogWriter {
    public static void logOperation(String tableName, String operation) {

        File outputfile= new File("C:/Users/Tudor/IdeaProjects/untitled/src/config/database_log.csv");

        SimpleDateFormat data= new SimpleDateFormat("yyyy-MM-dd 'at' HH:mm:ss");
        Date dataCurenta = new Date(System.currentTimeMillis());
        String log=tableName+","+operation+","+dataCurenta+"\n";

        try (PrintWriter pwriter = new PrintWriter(new FileOutputStream(outputfile, true) ) ) {
//            // System.out.println("ok");
//            StringBuilder logEntry = new StringBuilder();
//            logEntry.append(LocalDateTime.now()).append(",");
//            logEntry.append(tableName).append(",");
//            logEntry.append(operation).append("\n");
//
//            writer.write(logEntry.toString());
            pwriter.append(log);
        }
            catch (FileNotFoundException e){
                e.printStackTrace();
            }

//        } catch (IOException e) {
//            e.printStackTrace();
//        }
    }
}