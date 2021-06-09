import { Component, OnInit, OnDestroy } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import { Subscription } from 'rxjs';

import { BusinessCard } from '../business-card.model';
import { BusinessCardService } from '../business-card.service';

@Component({
  selector: 'app-edit-business-card',
  templateUrl: './edit-business-card.component.html',
  styleUrls: ['./edit-business-card.component.css']
})
export class EditBusinessCardComponent implements OnInit, OnDestroy {
  userID: string;
  cardID: string;
  card: BusinessCard;
  editBusinessCardForm: FormGroup;
  paramSub: Subscription;

  constructor(
    private formBuilder: FormBuilder,
    private route: ActivatedRoute,
    private cardsService: BusinessCardService,
    private router: Router
  ) { }

  ngOnInit() {
    this.paramSub = this.route.params.subscribe(params => {
      this.userID = params["userID"];
      this.cardID = params["cardID"];
    });

    this.editBusinessCardForm = this.formBuilder.group({
      firstName: ["", Validators.required],
      lastName: ["", Validators.required],
      phoneNumber: ["", Validators.required],
      emailAddress: ["", Validators.required],
      company: ["", Validators.required],
      additionalInfo: [""]
    });

    this.cardsService.getCard(this.userID, this.cardID)
      .valueChanges()
      .subscribe(doc => {
        this.editBusinessCardForm.controls.firstName.setValue(doc.firstName);
        this.editBusinessCardForm.controls.lastName.setValue(doc.lastName);
        this.editBusinessCardForm.controls.phoneNumber.setValue(doc.phoneNumber);
        this.editBusinessCardForm.controls.emailAddress.setValue(doc.emailAddress);
        this.editBusinessCardForm.controls.company.setValue(doc.company);
        this.editBusinessCardForm.controls.additionalInfo.setValue(doc.additionalInfo);
      });
  }

  ngOnDestroy() {
    this.paramSub.unsubscribe();
  }

  // convenience getter for easy access to form fields
  get f() { return this.editBusinessCardForm.controls; }

  onSubmit() {
      // stop here if form is invalid
      if (this.editBusinessCardForm.invalid) {
          return;
      }

      console.log(this.f.firstName.value + ", " + 
        this.f.lastName.value + ", " + 
        this.f.phoneNumber.value + ", " + 
        this.f.emailAddress.value + ", " + 
        this.f.company.value + ", " + 
        this.f.additionalInfo.value);

      let card = new BusinessCard();
      card.firstName = this.f.firstName.value;
      card.lastName = this.f.lastName.value;
      card.phoneNumber = this.f.phoneNumber.value;
      card.emailAddress = this.f.emailAddress.value;
      card.company = this.f.company.value;
      card.additionalInfo = this.f.additionalInfo.value;

      this.cardsService.updateCard(this.userID, this.cardID, card);
      this.router.navigate(['home']);
  }
}
