package org.example;

import com.mongodb.MongoClient;
import com.mongodb.MongoCredential;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;
import com.mongodb.client.result.UpdateResult;
import org.bson.Document;
import org.bson.conversions.Bson;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        MongoClient mongoClient = new MongoClient("127.0.0.1", 27017);
        MongoCredential credential;
        credential = MongoCredential.createCredential("root", "Assignment1", "root123".toCharArray());
        System.out.println("Connected to the database successfully");
        MongoDatabase database = mongoClient.getDatabase("31375_db");
        MongoCollection<Document> collection = database.getCollection("newCollection"); // Replace with your collection
                                                                                        // name
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Menu:");
            System.out.println("1. Create");
            System.out.println("2. Read");
            System.out.println("3. Update");
            System.out.println("4. Delete");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    // Create operation
                    createDocument(collection, scanner);
                    break;
                case 2:
                    // Read operation
                    readDocuments(collection);
                    break;
                case 3:
                    // Update operation
                    updateDocument(collection, scanner);
                    break;
                case 4:
                    // Delete operation
                    deleteDocument(collection, scanner);
                    break;
                case 5:
                    System.out.println("Exiting the program.");
                    mongoClient.close(); // Close the MongoDB connection
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please select a valid option.");
                    break;
            }
        }
    }

    private static void createDocument(MongoCollection<Document> collection, Scanner scanner) {
        System.out.print("Enter a key: ");
        String key = scanner.next();
        System.out.print("Enter a value: ");
        String value = scanner.next();
        Document document = new Document(key, value);
        collection.insertOne(document);
        System.out.println("Document added successfully.");
    }

    private static void readDocuments(MongoCollection<Document> collection) {
        for (Document doc : collection.find()) {
            System.out.println(doc.toJson());
        }
    }

    private static void updateDocument(MongoCollection<Document> collection, Scanner scanner) {
        System.out.print("Enter the key of the document to update: ");
        String key = scanner.next();
        System.out.print("Enter the previous value: ");
        String value = scanner.next();
        Document filter = new Document(key, value);
        System.out.print("Enter the new value: ");
        String newValue = scanner.next();
        Document update = new Document("$set", new Document(key, newValue));
        collection.updateMany(filter, update);
        System.out.println("Document updated successfully.");
    }

    private static void deleteDocument(MongoCollection<Document> collection, Scanner scanner) {
        System.out.print("Enter the key of the document to delete: ");
        String key = scanner.next();
        System.out.print("Enter the value of the document to delete: ");
        String value = scanner.next();
        Document filter = new Document(key, value);
        collection.deleteOne(filter);
        System.out.println("Document deleted successfully.");
    }
}