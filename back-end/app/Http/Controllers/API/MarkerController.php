<?php

namespace App\Http\Controllers\API;

use App\Models\Marker;
use App\Http\Requests\MarkerRequest;
use App\Http\Controllers\Controller;
use Illuminate\Http\Request;

class MarkerController extends Controller
{
    /**
     * Display a listing of the resource.
     */
    public function index()
    {
        $marker = Marker::all();
        return response()->json([
            'message' => 'OK',
            'marker' => $marker,
        ], 200);
    }

    /**
     * Store a newly created resource in storage.
     */
    public function store(Request $request)
    {
        $marker = Marker::create($request->all());
        return response()->json([
            'message' => 'OK',
            'marker' => $marker,
        ], 201);
    }

    /**
     * Display the specified resource.
     */
    public function show(string $id)
    {
        $marker = Marker::find($id);
        if(!$marker)
            return response()->json([
                'message' => 'Dados nao encontrados',
            ], 404);
        return response()->json([
            'message' => 'OK',
            'marker' => $marker,
        ], 200);
    }

    /**
     * Update the specified resource in storage.
     */
    public function update(Request $request, string $id)
    {
        $marker = Marker::find($id);
        if(!$marker)
            return response()->json([
                'message' => 'Dados nao encontrados',
                'marker' => null,
            ], 404);
        $marker->update($request->all());
        return response()->json([
            'message' => 'OK',
            'marker' => $marker,
        ], 200);
    }

    /**
     * Remove the specified resource from storage.
     */
    public function destroy(string $id)
    {
        $marker = Marker::find($id);
        if(!$marker)
            return response()->json([
                'message' => 'Dados nao encontrados',
                'marker' => null,
            ], 404);
        $marker->delete();
        return response()->json([
            'message' => 'Dados removidos',
            'marker' => $marker,
        ], 200);
    }
}
