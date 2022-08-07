package pfaron;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.time.Instant;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class Form {
    private final static String FILE = "form_history.txt";
    private final static String SEPARATION_SYMBOL = "$&&";

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/form", new FormHandler());
        server.setExecutor(null);
        server.start();
    }

    static class FormHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange httpEx) throws IOException {

            System.out.println("Initializing handle");

            final var params = httpEx.getRequestURI().getQuery();
            if (params != null && !params.equals("")) {
                writeToFile(params);
            }

            System.out.println("Building response");

            final var sb = new StringBuilder();

            appendBeginning(sb);
            appendFileContent(sb);
            appendEnding(sb);

            final var response = sb.toString();

            System.out.println("Sending response: \n" + response);

            httpEx.getResponseHeaders().set("Content-Type", "text/html; charset=UTF-8");

            httpEx.sendResponseHeaders(200, response.getBytes().length);

            try (final var out = new OutputStreamWriter(httpEx.getResponseBody(), StandardCharsets.UTF_8)) {
                out.write(response);
                out.flush();
            }
        }
    }

    private static void writeToFile(final String params) throws IOException {
        System.out.println("Processing params: " + params);

        final var paramsPairs = params.split("&");

        final var output = new String[2]; // 0 - nick, 1 - content

        for (var pair : paramsPairs) {

            final var nameAndValue = pair.split("=");

            System.out.println("pair: " + pair);

            if (nameAndValue.length < 2) {
                System.out.println("skipping");
                continue;
            }

            switch (nameAndValue[0]) {
                case "nick" -> output[0] = nameAndValue[1];
                case "text" -> output[1] = nameAndValue[1];
                default -> System.out.println("Incorrect parameter: " + nameAndValue[0]);
            }
        }

        System.out.println("Output is: " + output[0] + "\n" + output[1]);

        try (final var writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(FILE, true), StandardCharsets.UTF_8))) {
            if (output[0] != null && output[1] != null) {
                System.out.println("Decoded output is: " + decode(output[0]) + "\n" + decode(output[1]));
                var currentDate = Instant.now().toString();
                writer.append(currentDate.substring(0, currentDate.indexOf("T")))
                        .append(" ")
                        .append(currentDate.substring(currentDate.indexOf("T") + 1, currentDate.indexOf(".")))
                        .append("\n")
                        .append(decode(output[0])).append("\n")
                        .append(decode(output[1])).append("\n")
                        .append(SEPARATION_SYMBOL).append("\n");

                writer.flush();
            }
        }
    }

    private static void appendBeginning(StringBuilder sb) {
        sb.append("<!DOCTYPE html>\n");
        sb.append("<html>\n");
        sb.append("""
                  <head>
                    <meta charset="UTF-8" />
                    <title>URL Encoded Forms</title>
                  </head>
                """);
        sb.append("  <body>\n");
        sb.append("""
                   <form method="get">
                     <label for="nick">Your nick:</label>
                     <input type="text" id="nick" name="nick"><br><br>
                     <label for="text">Content:</label>
                     <textarea rows="5" cols="50" id="text" name="text"></textarea>
                     <input type="submit" value="Submit">
                   </form>
                """);
        sb.append("<br>\n");
    }

    private static void appendFileContent(StringBuilder sb) throws IOException {
        try (final var reader = new BufferedReader(new InputStreamReader(new FileInputStream(FILE), StandardCharsets.UTF_8))) {
            String line;

            while ((line = reader.readLine()) != null) {
                sb.append(line).append("<br>\n");

                line = reader.readLine();
                sb.append("<b>").append(line).append("</b>").append("<br>\n");

                while (!(line = reader.readLine()).equals(SEPARATION_SYMBOL))
                    sb.append(line).append("<br>\n");

                sb.append("<br>");

            }
        }
    }

    private static void appendEnding(StringBuilder sb) {
        sb.append("  </body>\n");
        sb.append("</html>\n");
    }

    private static String decode(final String value) {
        return URLDecoder.decode(value, StandardCharsets.UTF_8);
    }
}
