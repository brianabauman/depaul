import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

import { BusinessCard } from '../business-card.model';
import { BusinessCardService } from '../business-card.service';
import { AuthService } from '../auth.service';
import { Router } from '@angular/router';

import { FilterPipe }from '../filter.pipe'

@Component({
  selector: 'app-business-card-list',
  templateUrl: './business-card-list.component.html',
  styleUrls: ['./business-card-list.component.css']
})
export class BusinessCardListComponent implements OnInit {
  cards: Observable<any>

  constructor(
    private authService: AuthService, 
    private cardService: BusinessCardService,
    private router: Router
  ) { }

  ngOnInit() {
    this.cards = this.cardService.getCards(this.authService.userID)
      .snapshotChanges()
      .pipe(map(actions => {
        return actions.map(a => {
            //Get document data
            const data = a.payload.doc.data() as BusinessCard;
            //Get document id
            const id = a.payload.doc.id;
            //Use spread operator to add the id to the document data
            return { id, ...data };
        });
      }));
  }

  editCard(card: any) {
    this.router.navigate([`edit/${this.authService.userID}/${card.id}`])
  }

  deleteCard(card: any) {
    this.cardService.deleteCard(this.authService.userID, card.id);
  }
}
