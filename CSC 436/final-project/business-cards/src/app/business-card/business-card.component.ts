import { Component, OnInit, Input } from '@angular/core';
import { Router } from '@angular/router';

import { BusinessCard } from '../business-card.model';
import { AuthService } from '../auth.service';
import { BusinessCardService } from '../business-card.service';

@Component({
  selector: 'app-business-card',
  templateUrl: './business-card.component.html',
  styleUrls: ['./business-card.component.css']
})
export class BusinessCardComponent implements OnInit {
  @Input() card: BusinessCard;

  constructor(
    private authService: AuthService,
    private cardService: BusinessCardService,
    private router: Router
  ) { }

  ngOnInit() {
  }

  editCard(card: any) {
    this.router.navigate([`edit/${this.authService.userID}/${card.id}`])
  }

  deleteCard(card: any) {
    this.cardService.deleteCard(this.authService.userID, card.id);
  }
}
