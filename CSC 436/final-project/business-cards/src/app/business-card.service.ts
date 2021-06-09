import { Injectable } from "@angular/core";
import {
    AngularFirestore,
    AngularFirestoreCollection,
    AngularFirestoreDocument
} from "@angular/fire/firestore";

import { BusinessCard } from './business-card.model';

@Injectable({
  providedIn: 'root'
})
export class BusinessCardService {

  constructor(private db: AngularFirestore) { }

  getCard(userID: string, cardID: string): AngularFirestoreDocument<BusinessCard> {
    return this.db.collection(`business-cards/${userID}/cards`).doc<BusinessCard>(cardID);
  }

  getCards(userID: string): AngularFirestoreCollection<BusinessCard> {
    return this.db.collection(`business-cards/${userID}/cards`);
  }

  createCollection(userID: string) {
    this.db.collection(`business-cards/${userID}/cards`).add({
        firstName: "John",
        lastName: "Doe",
        phoneNumber: "(123) 456-7890",
        emailAddress: "john.doe@gmail.com",
        company: "John Doe, Inc.",
        additionalInfo: ""
    });
  }

  addCard(userID: string, card: BusinessCard) {
    this.db.collection<BusinessCard>(`business-cards/${userID}/cards`).add(Object.assign({}, card));
  }
  
  updateCard(userID: string, cardID: string, newCard: BusinessCard) {
    this.db.collection<BusinessCard>(`business-cards/${userID}/cards`).doc<BusinessCard>(cardID).set(Object.assign({}, newCard));
  }

  deleteCard(userID: string, cardID: string) {
    this.db.collection<BusinessCard>(`business-cards/${userID}/cards`).doc(cardID).delete();
  }
}