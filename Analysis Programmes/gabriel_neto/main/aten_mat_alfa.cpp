#include "data_colector.cpp"

int main(){

    data_colector alfa1("input/LAB5_AM_VACUO.ASC");
    vector<double> x1 = alfa1.get_a_certain_col(1);
    vector<double> y1 = alfa1.get_a_certain_col(2);

    data_colector alfa2("input/LAB5_AM_AR.ASC");
    vector<double> x2 = alfa2.get_a_certain_col(1);
    vector<double> y2 = alfa2.get_a_certain_col(2);
    
    
    /*vector<int> pos_to_erase;
    int counter = 0;

    for (int i = 0; i < y.size(); i++){
        
        if (y[i] != 0.00){
            
            y[i] = log10(y[i]);
        }

        else {

            pos_to_erase.push_back(i);
        }
    }

    for (int pos : pos_to_erase){

        x.erase(x.begin() + pos - counter);
        y.erase(y.begin() + pos - counter);

        counter += 1; 
    } LOG */

    double* x1_ptr = &x1[0];
    double* y1_ptr = &y1[0];
    Int_t points_numb1 = x1.size();

    double* x2_ptr = &x2[0];
    double* y2_ptr = &y2[0];
    Int_t points_numb2 = x2.size();

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);

    TGraph* g1 = new TGraph(points_numb1, x1_ptr, y1_ptr);

    TGraph* g2 = new TGraph(points_numb2, x2_ptr, y2_ptr);

    g1->SetMarkerStyle(4);
    g1->SetMarkerColor(kGreen-3);
    g1->SetLineColor(kGreen+4);
    g1->SetLineWidth(1.75);
    g2->GetXaxis()->SetTitle("Channels");
    g2->GetXaxis()->SetLimits(500, 730);
    g2->GetXaxis()->SetNdivisions(-523);

    g2->SetMarkerStyle(4);
    g2->SetMarkerColor(kAzure+7);
    g2->SetLineColor(kBlue+1);
    g2->SetLineWidth(1.75);

    /*g->GetXaxis()->SetLimits(400, 650);
    g->GetXaxis()->SetNdivisions(-525); AR*/

    /*g->GetXaxis()->SetLimits(0, 525);
    g->GetXaxis()->SetNdivisions(-521); LOG */

    g2->GetXaxis()->SetLabelSize(0.028);
    g2->GetXaxis()->SetTickLength(-0.04);
    g2->GetXaxis()->SetLabelOffset(0.033);
    g2->GetXaxis()->SetTitleOffset(1.3);
    g2->GetYaxis()->SetTitle("Absolute frequency");
    g2->GetYaxis()->SetLabelSize(0.028);
    g2->GetYaxis()->SetRangeUser(0, 45000);
    g2->GetYaxis()->SetNdivisions(-315);

    /*g->GetYaxis()->SetRangeUser(0, 5000);
    g->GetYaxis()->SetNdivisions(-510); AR */

    /*g->GetYaxis()->SetRangeUser(0, 4.5);
    g->GetYaxis()->SetNdivisions(-509); LOG */

    g2->Draw("APL");
    g1->Draw("PL SAME");

    C->Update();
    C->SaveAs("output/2_lines_aten_mat.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g1;
    delete g2;
    delete A;

    return 0;
}
